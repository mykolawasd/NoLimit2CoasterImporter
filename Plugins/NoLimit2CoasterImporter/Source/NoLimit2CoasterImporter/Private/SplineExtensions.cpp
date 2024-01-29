// Mykola Shevchenko, All Rights Reserved


#include "../Public/SplineExtensions.h"

#include "Components/SplineComponent.h"

void USplineExtensions::RollSplinePoint(USplineComponent* Target, const int32 PointIndex, float Deg, bool UpdateSpline)
{
	if (PointIndex < 0 || PointIndex > Target->GetNumberOfSplinePoints()) return;

	FInterpCurveQuat& SplineRotation = Target->GetSplinePointsRotation();
	FInterpCurvePoint<FQuat>& EditedRotPoint = SplineRotation.Points[PointIndex];

	const auto PointTransform = Target->GetTransformAtSplinePoint(PointIndex, ESplineCoordinateSpace::Local);
	EditedRotPoint.OutVal = FRotator(PointTransform.Rotator().Pitch, PointTransform.Rotator().Yaw, Deg).Quaternion();

	if (UpdateSpline) Target->UpdateSpline();
	Target->bSplineHasBeenEdited = true;
}
