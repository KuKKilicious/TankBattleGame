// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::AimAt(FVector aimLocation)
{
	if(!TankAimingComponent){return ;}
	TankAimingComponent->AimAt(aimLocation,m_FiringVelocity);
}



void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();

	if(!ensure(m_Barrel)){	
		return;}
	
	bool isReloaded = (FPlatformTime::Seconds() - m_LastFireTime) > m_ReloadTimeInSeconds;
	if(isReloaded)
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(m_sphereProjectile,m_Barrel->GetSocketLocation(FName("Projectile")),m_Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(m_FiringVelocity);
		m_LastFireTime = FPlatformTime::Seconds();
	}

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent); 

}

