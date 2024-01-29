// Mykola Shevchenko, All Rights Reserved


#include "CartBase.h"

#include "NL2_SplineGenBase.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"

ACartBase::ACartBase()
{
	PrimaryActorTick.bCanEverTick = true;
	EngineCarMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	if (EngineCarMeshComp)
	{
		EngineCarMeshComp->SetupAttachment(GetRootComponent());
	}
	EngineCarMeshComp->SetCollisionProfileName(TEXT("OverlapAll"));
	
}

void ACartBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	GetWorldTimerManager().SetTimer(TimerHandle_TickDelay, this, &ACartBase::EnableTick, DelayStart, false);
	
}

void ACartBase::Tick(float DeltaTime)
{
	DistanceAlongSpline = DeltaTime * Speed + DistanceAlongSpline;
	UpdateEngine();
	
	if (bLoop && DistanceAlongSpline >= NL2_Track->SplineForMovement->GetSplineLength()) DistanceAlongSpline = 0;

	Super::Tick(DeltaTime);
}

void ACartBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	UpdateEngine();
}

void ACartBase::UpdateEngine() const
{
	if (!NL2_Track) return;
	if (!IsValid(EngineCarMeshComp)) return;

	const auto SplinePointTransform =
		NL2_Track->SplineForMovement->GetTransformAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::Local);
	const auto Location = SplinePointTransform.GetLocation();
	const auto Rotation = SplinePointTransform.GetRotation();
	const auto Up = Height * Rotation.GetAxisZ();  // This vector is above the spline by Height units
	
	EngineCarMeshComp->SetRelativeLocation(Location + Up);
	EngineCarMeshComp->SetRelativeRotation(Rotation);
}


