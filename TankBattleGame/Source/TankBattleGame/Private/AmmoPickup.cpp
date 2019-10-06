// //KuKKi ©2019

#include "Components/StaticMeshComponent.h"
#include "AmmoPickup.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotatePickup(DeltaTime, m_rotDegreePsec);
}

AAmmoPickup::AAmmoPickup()
{
	name = "Ammo";
	value = 25;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	SetRootComponent(m_Mesh);
}

void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	m_Mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAmmoPickup::OnOverlap);
}

void AAmmoPickup::RotatePickup(float delta_time, float rotPsec)
{
	auto rotation = FRotator(0, rotPsec *delta_time, 0);
	FQuat quatRotation = FQuat(rotation);

	AddActorLocalRotation(quatRotation);
}
void AAmmoPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto TankAimingComponent = OtherActor->FindComponentByClass<UTankAimingComponent>();
	auto Tank = Cast<ATank> (OtherActor);
	if (Tank &&Tank->IsPlayerControlled())
	{
		if (TankAimingComponent && TankAimingComponent->AddAmmo(value))
		{
			Destroy();
		}
	}
}