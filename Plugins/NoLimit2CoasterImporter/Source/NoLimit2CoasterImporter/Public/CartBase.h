// Mykola Shevchenko, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CartBase.generated.h"

class ANL2_SplineGenBase;

UCLASS()
class NOLIMIT2COASTERIMPORTER_API ACartBase : public AActor
{
	GENERATED_BODY()

public:
	ACartBase();

protected:
	void EnableTick() { SetActorTickEnabled(true); };
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;

	void UpdateEngine() const;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Cart")
	ANL2_SplineGenBase* NL2_Track;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cart")
	UStaticMeshComponent* EngineCarMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cart")
	float Speed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cart")
	bool bLoop = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cart")
	float Height = 10.0f;  // Height of cart above spline

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cart")
	float DelayStart = 5.0f;

private:
	float DistanceAlongSpline = 0.0f;
	
	FTimerHandle TimerHandle_TickDelay;
};
