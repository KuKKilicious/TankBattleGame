// //KuKKi ©2019


#include "TankTrack.h"
#include "SprungWheel.h"
#include "WheelSpawn.h"


void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	SetNotifyRigidBodyCollision(true);

}

void UTankTrack::DriveTrack(float ForceToApply)
{

	auto forceApplied = ForceToApply * m_TrackMaxDrivingForce * 100 * m_BoostMultiplier;
	UE_LOG(LogTemp, Warning, TEXT("%f"),m_BoostMultiplier);
	auto Wheels = GetWheels();
	auto ForcePerWheel = forceApplied / Wheels.Num();
	for (ASprungWheel* wheel : Wheels)
	{
		wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::setThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp(Throttle, -1.f, 1.0f);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::setMultiplier(float boost)
{
	m_BoostMultiplier = boost;
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> children;
	TArray<ASprungWheel*> wheels;
	GetChildrenComponents(true,children);
	for (USceneComponent* child: children)
	{
		auto spawnChild = Cast<UWheelSpawn>(child);
		if(!spawnChild){continue;}

		AActor* spawnedChild = spawnChild->getSpawnedActor();
		auto sprungWheel = Cast<ASprungWheel>(spawnedChild);
		if(!sprungWheel){continue;}
		wheels.Add(sprungWheel);
	}
	return wheels;
}
