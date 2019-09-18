// //KuKKi ©2019


#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{

	relativeSpeed = FMath::Clamp<float>(relativeSpeed,-1.f,1.f);
	auto ElevationChange = relativeSpeed * m_MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp<float>( RelativeRotation.Pitch +ElevationChange,m_MinimumElevation,m_MaxElevation);
	SetRelativeRotation(FRotator(RawNewElevation,0,0));
}
