// //KuKKi ©2019


#include "Public/TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	m_Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	m_Turret = TurretToSet;
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
		firingVelocity, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(), false
	))
	{


		auto AimDirection = launchVelocity.GetSafeNormal();

		MoveTowards(AimDirection);

	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: no projectile Velocity found"), Time);
	}
}

void UTankAimingComponent::MoveTowards(const FVector& aimDirection)
{
	//Rotate barrel from base socket (connection to upper tank unit) 
	auto barrelRotator = m_Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = aimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - barrelRotator;

	m_Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		m_Turret->Yawing(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		m_Turret->Yawing(-DeltaRotator.Yaw);
	}
}







