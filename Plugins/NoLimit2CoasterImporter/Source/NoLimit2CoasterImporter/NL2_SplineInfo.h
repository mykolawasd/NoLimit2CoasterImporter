// Mykola Shevchenko, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "NL2_SplineInfo.generated.h"

/**
 * Structure for storing spline information from No Limit 2 (NL2).
 */
USTRUCT(BlueprintType)
struct FNL2_SplineInfo : public FTableRowBase
{
 GENERATED_BODY()

 UPROPERTY(VisibleAnywhere)
 float PosX = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float PosY = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float PosZ = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float FrontX = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float FrontY = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float FrontZ = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float LeftX = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float LeftY = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float LeftZ = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float UpX = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float UpY = 0.0f;

 UPROPERTY(VisibleAnywhere)
 float UpZ = 0.0f;
};
