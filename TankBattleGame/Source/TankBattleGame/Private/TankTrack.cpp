// //KuKKi ©2019


#include "TankTrack.h"

void UTankTrack::setThrottle(float value)
{
	value = FMath::Clamp(value,-1.f,1.0f);
	auto forceApplied = GetForwardVector() * value * m_TrackMaxDrivingForce*100;
	auto forceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(forceApplied,forceLocation);
}
