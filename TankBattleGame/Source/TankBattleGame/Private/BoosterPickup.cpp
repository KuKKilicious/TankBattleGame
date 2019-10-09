// //KuKKi ©2019


#include "BoosterPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Tank.h"
#include "TankMovementComponent.h"

ABoosterPickup::ABoosterPickup()
{
	name = "Booster";
	value = 10000.f; //not used 


	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body"));
	SetRootComponent(m_Mesh);
}

void ABoosterPickup::BeginPlay()
{
	Super::BeginPlay();
	m_Mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABoosterPickup::OnOverlap);
}

void ABoosterPickup::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	auto Tank = Cast <ATank>(OtherActor);
	if (Tank &&Tank->IsPlayerControlled())
	{
		auto movementComp =   Cast<UTankMovementComponent>(OtherActor->FindComponentByClass<UTankMovementComponent>());
		if (movementComp)
		{
			movementComp->Boosting();


			Destroy();
		}
	}
}

void ABoosterPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotatePickup(DeltaTime,m_rotDegreePsec);
}

void ABoosterPickup::RotatePickup(float delta_time, float rotPsec)
{
	auto rotation = FRotator(0, rotPsec *delta_time, 0);
	FQuat quatRotation = FQuat(rotation);

	AddActorLocalRotation(quatRotation);
}

