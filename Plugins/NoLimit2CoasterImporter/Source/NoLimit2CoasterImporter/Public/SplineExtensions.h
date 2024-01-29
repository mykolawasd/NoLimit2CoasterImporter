// Mykola Shevchenko, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SplineExtensions.generated.h"

class USplineComponent;

/**
 * Custom Blueprint Function Library for spline manipulation.
 */
UCLASS()
class NOLIMIT2COASTERIMPORTER_API USplineExtensions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// BlueprintCallable function to roll a specific point on a spline.
	// @param Target: The target spline component to manipulate.
	// @param PointIndex: Index of the spline point to roll.
	// @param Deg: The amount of rotation in degrees to apply to the specified spline point.
	UFUNCTION(BlueprintCallable, Category = "Splines")
	static void RollSplinePoint(USplineComponent* Target, const int32 PointIndex, float Deg,  bool UpdateSpline = true);
};
