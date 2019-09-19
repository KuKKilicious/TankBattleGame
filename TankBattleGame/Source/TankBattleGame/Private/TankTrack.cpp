// //KuKKi ©2019


#include "TankTrack.h"

void UTankTrack::setThrottle(float value)
{

	auto forceApplied = GetForwardVector() * value * m_TrackMaxDrivingForce*100;
	auto forceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(forceApplied,forceLocation);
	UE_LOG(LogTemp, Warning, TEXT("throttle %f"),forceApplied.X);
}
