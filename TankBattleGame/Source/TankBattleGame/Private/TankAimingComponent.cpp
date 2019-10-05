// //KuKKi ©2019


#include "Public/TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool isReloaded = (FPlatformTime::Seconds() - m_LastFireTime) > m_ReloadTimeInSeconds;
	if(m_AmmoCount<=0)
	{
		firingStatus = EFiringStatus::OutOfAmmo;
	}
	else if (!isReloaded)
	{
		firingStatus = EFiringStatus::Reloading;
	}
	else if (isBarrelMoving())
	{
		firingStatus = EFiringStatus::Aiming;
	}
	else
	{
		firingStatus = EFiringStatus::Locked;
	}


}


void UTankAimingComponent::AimAt(FVector aimLocation)
{
	if (!ensure(m_Barrel)) { return; }

	FVector launchVelocity(0);
	FVector startLocation = m_Barrel->GetSocketLocation(FName("Projectile"));
	//calculate launcVelocity


	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		launchVelocity,
		startLocation,
		aimLocation,
		m_FiringVelocity, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace, FCollisionResponseParams::DefaultResponseParam, TArray<AActor *>(), false
	))
	{

		m_CurrentAimDirection = launchVelocity.GetSafeNormal();

		MoveTowards(m_CurrentAimDirection);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: no projectile Velocity found"), Time);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet &&TurretToSet)) { return; }
	m_Barrel = BarrelToSet;
	m_Turret = TurretToSet;
}

int32 UTankAimingComponent::getAmmoCount() const
{
	return m_AmmoCount;
}

void UTankAimingComponent::setProjectile(UClass* projectile)
{
	if(!ensure(projectile)){return;}
	m_Projectile = projectile;
}


void UTankAimingComponent::Fire()
{

	if (firingStatus == EFiringStatus::Locked && m_AmmoCount >0)
	{
		if (!ensure(m_Barrel&&m_Projectile)) {
			return;
		}
		auto projectile = GetWorld()->SpawnActor<AProjectile>(m_Projectile, m_Barrel->GetSocketLocation(FName("Projectile")), m_Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(m_FiringVelocity);
		m_LastFireTime = FPlatformTime::Seconds();
		
		m_AmmoCount--;
	}
}

bool UTankAimingComponent::isBarrelMoving()
{
	bool moving = !(m_Barrel->GetForwardVector().Equals(m_CurrentAimDirection,0.05f));
	return moving;
}


void UTankAimingComponent::BeginPlay()
{
	m_LastFireTime = FPlatformTime::Seconds();
}

EFiringStatus UTankAimingComponent::getFiringStatus() const
{
	return firingStatus;
}

bool UTankAimingComponent::AddAmmo(float value)
{
	m_AmmoCount+=value;
	return true;
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
