// //KuKKi ©2019


#include "Turret.h"
#include "Components/StaticMeshComponent.h"

float ATurret::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	int32  damage = (FMath::Clamp(FPlatformMath::RoundToInt(Damage), 0, m_TankHP));
	if ( m_TankHP - damage <=0)
	{
		UStaticMeshComponent* staticMesh = FindComponentByClass<UStaticMeshComponent>();
		staticMesh->SetSimulatePhysics(true);
		staticMesh->SetMassOverrideInKg(FName(NAME_None),0.1f);
		staticMesh->AddImpulse(FVector(0.f,0.f, 10000.f));
	}
	return Super::TakeDamage(Damage,DamageEvent,EventInstigator,DamageCauser);

}
