// //KuKKi ©2019


#include "HealthPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.h"

void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();


	m_Mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &AHealthPickup::OnOverlap);
}

AHealthPickup::AHealthPickup()
{
	name = "Health";
	value = 25;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	//auto root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(m_Mesh);
}


void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotatePickup(DeltaTime, m_rotDegreePsec);
}

void AHealthPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Tank = Cast <ATank>(OtherActor);
	if (Tank &&Tank->IsPlayerControlled())
	{
		if (Tank->AddHealth(value))
		{
			Destroy();
		}
	}
}

void AHealthPickup::RotatePickup(float delta_time, float rotPsec)
{
	auto rotation = FRotator(0, rotPsec *delta_time, 0);
	FQuat quatRotation = FQuat(rotation);

	AddActorLocalRotation(quatRotation);
}

