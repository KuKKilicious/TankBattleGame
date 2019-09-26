// //KuKKi ©2019


#include "TankTrack.h"

void UTankTrack::ApplySidewaysForce()
{
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto velocity = TankRoot->GetComponentVelocity();

	auto right = GetRightVector();
	//Calculate slippage speed
	auto slipSpeed = FVector::DotProduct(velocity, right);

	auto DeltaTime = GetWorld()->DeltaTimeSeconds;

	//required accel this frame to correct
	auto correctionAcceleration = -slipSpeed / DeltaTime * GetRightVector();

	//apply sideways force
	auto correctionForce = (TankRoot->GetMass() * correctionAcceleration) / 2;
	TankRoot->AddForce(correctionForce);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	SetNotifyRigidBodyCollision(true);

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY TANKTRACK"))
}

void UTankTrack::DriveTrack()
{
	
	auto forceApplied = GetForwardVector() * m_CurrentThrottle * m_TrackMaxDrivingForce * 100;
	auto forceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(forceApplied, forceLocation);
}

void UTankTrack::setThrottle(float Throttle)
{
	m_CurrentThrottle = FMath::Clamp(m_CurrentThrottle + Throttle, -1.f, 1.0f);
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();

	ApplySidewaysForce();


	m_CurrentThrottle = 0.f;

}
