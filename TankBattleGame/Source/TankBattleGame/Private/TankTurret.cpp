// //KuKKi ©2019


#include "TankTurret.h"

void UTankTurret::Yawing(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1.f, 1.f);
	auto YawChange = relativeSpeed * MaxDegreesPerSecond() * GetWorld()->DeltaTimeSeconds;
	auto RawNewYaw =RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, RawNewYaw, 0));
}
