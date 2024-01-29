// Mykola Shevchenko, All Rights Reserved


#include "NL2_SplineGenBase.h"

#include "SplineExtensions.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "NoLimit2CoasterImporter/NL2_SplineInfo.h"
#include "DrawDebugHelpers.h"

constexpr float GNoLimitMultiplayer = 100; // Multiplier for Location
TArray<FVector> SplineLocations;
TArray<FQuat> SplineQuaternions;

ANL2_SplineGenBase::ANL2_SplineGenBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	if (Spline) Spline->SetMobility(EComponentMobility::Static);
	
	SplineForMovement = CreateDefaultSubobject<USplineComponent>("SplineForMovement");
	if (SplineForMovement) SplineForMovement->SetMobility(EComponentMobility::Static);
}

void ANL2_SplineGenBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (bBuild)
	{
		if (IsValid(MaterialTrack)) Model->SetMaterial(0, MaterialTrack);
		BuildMeshes();
	}
}

void ANL2_SplineGenBase::BeginPlay()
{
	Super::BeginPlay();
}

void ANL2_SplineGenBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANL2_SplineGenBase::BuildNL2Track()
{
	if (!DataTable) return;

	Spline->ClearSplinePoints();
	
	for (const auto& It : DataTable->GetRowMap())
	{
		const FNL2_SplineInfo* OutRow = reinterpret_cast<FNL2_SplineInfo*>(It.Value);

		// The scale of NoLimit is different from UE so it needs to be multiplied
		const FVector Location =
			FVector(OutRow->PosX * GNoLimitMultiplayer, OutRow->PosZ * GNoLimitMultiplayer, OutRow->PosY * GNoLimitMultiplayer) + Offset;

		Spline->AddSplinePoint(Location, ESplineCoordinateSpace::Local, false);

		const FVector FrontVector = FVector(OutRow->FrontX, OutRow->FrontZ, OutRow->FrontY);
		const FVector LeftVector = FVector(OutRow->LeftX, OutRow->LeftZ, OutRow->LeftY);
		const FVector UpVector = FVector(OutRow->UpX, OutRow->UpZ, OutRow->UpY);

		FMatrix Matrix(FrontVector, -LeftVector, UpVector, FVector(0, 0, 1));
		SplineQuaternions.Add(Matrix.ToQuat());
		SplineLocations.Add(Location);
	}

	// It works correctly if you only set Roll after creating all the points
	for (int32 i = 0; i < Spline->GetNumberOfSplinePoints(); i++)
	{
		const float RollRad = FMath::DegreesToRadians(SplineQuaternions[i].Rotator().Roll);
		USplineExtensions::RollSplinePoint(Spline, i, RollRad, true);
	}
	
	BuildSplinePoints();
}

void ANL2_SplineGenBase::BuildSplinePoints()
{
	for (int32 i = 0; i < Spline->GetNumberOfSplineSegments(); i++)
	{
		const FVector StartPos = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector StartTangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const FVector EndPos = Spline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		const FVector EndTangent = Spline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		const FVector InUpSplineDir = Spline->GetDefaultUpVector(ESplineCoordinateSpace::Local);
		const float StartRoll = Spline->GetRollAtSplinePoint(i, ESplineCoordinateSpace::Local);
		const float EndRoll = Spline->GetRollAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
		BuildMesh(StartPos, StartTangent, EndPos, EndTangent, InUpSplineDir, StartRoll, EndRoll);
	}

	const int32 NumberOfPoints = Spline->GetNumberOfSplinePoints();
	Spline->ClearSplinePoints();

	SplineForMovement->ClearSplinePoints();
	for (int32 i = 0; i < NumberOfPoints; i++)
	{
		SplineForMovement->AddSplinePoint(SplineLocations[i], ESplineCoordinateSpace::Local, false);
		SplineForMovement->SetRotationAtSplinePoint(i, SplineQuaternions[i].Rotator(), ESplineCoordinateSpace::Local, false);
		SplineForMovement->SetSplinePointType(i, ESplinePointType::Curve, true);
	}
	
}

void ANL2_SplineGenBase::BuildMesh(const FVector& StartPos, const FVector& StartTangent, const FVector& EndPos,
                                   const FVector& EndTangent, const FVector& InUpSplineDir, float StartRoll, float EndRoll)
{
	USplineMeshComponent* Smc = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
	if (!Smc) return;

	Smc->AttachToComponent(Spline, FAttachmentTransformRules::KeepRelativeTransform);
	Smc->RegisterComponent();
	AddInstanceComponent(Smc);

	Smc->SetStaticMesh(Model);
	SplineMeshes.Add(Smc);
	Smc->SetStartAndEnd(StartPos, StartTangent, EndPos, EndTangent, false);
	Smc->SetSplineUpDir(InUpSplineDir, false);
	Smc->SetStartRoll(StartRoll, false);
	Smc->SetEndRoll(EndRoll, true);

	Smc->SetMobility(EComponentMobility::Static);

	Smc->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Smc->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
}

void ANL2_SplineGenBase::BuildMeshes()
{
	while (SplineMeshes.Num() > 0)
	{
		SplineMeshes[0]->DestroyComponent();
		SplineMeshes.RemoveAt(0);
	}

	if (!IsValid(Model)) return;

	BuildNL2Track();
}


