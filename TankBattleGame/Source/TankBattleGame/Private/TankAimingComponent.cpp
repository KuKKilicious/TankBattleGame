// //KuKKi ©2019


#include "Public/TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	m_Barrel = BarrelToSet;
}



void UTankAimingComponent::AimAt(FVector aimLocation, float firingVelocity)
{
	if (!m_Barrel) { return; }

	FVector launchVelocity(0);
	FVector startLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	//calculate launcVelocity


	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		aimLocation,
		firingVelocity, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::TraceFullPath, FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(), true)
		)
	{


	auto AimDirection = launchVelocity.GetSafeNormal();
	
	 MoveBarrelTowards(AimDirection);
	

	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& aimDirection)
{
	//Rotate barrel from base socket (connection to upper tank unit) 
	auto barrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - barrelRotator;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *barrelRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *AimAsRotator.ToString());
	//need speed
	//might just rotate pitch , limited degrees

	// Might move upper tank unit as well for yaw
}



