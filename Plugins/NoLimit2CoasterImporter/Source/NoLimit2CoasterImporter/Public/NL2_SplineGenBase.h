// Mykola Shevchenko, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NL2_SplineGenBase.generated.h"

class USplineMeshComponent;
class USplineComponent;
class UDataTable;

UCLASS()
class NOLIMIT2COASTERIMPORTER_API ANL2_SplineGenBase : public AActor
{
	GENERATED_BODY()

public:
	ANL2_SplineGenBase();

	void BuildNL2Track();
	void BuildMeshes();
	void BuildSplinePoints();
	void BuildMesh(const FVector& StartPos, const FVector& StartTangent, const FVector& EndPos, const FVector& EndTangent,
	               const FVector& InUpSplineDir, float StartRoll, float EndRoll);
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, Category = "Spline")
	USplineComponent* Spline;

	UPROPERTY(BlueprintReadWrite, Category = "Spline")
	USplineComponent* SplineForMovement;

	UPROPERTY()
	TArray<USplineMeshComponent*> SplineMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* Model;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UMaterialInterface* MaterialTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UDataTable* DataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	bool bBuild = false;

	// A shift for the roller coaster in the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	FVector Offset = FVector(0.0f, 0.0f, 0.0f);

};
