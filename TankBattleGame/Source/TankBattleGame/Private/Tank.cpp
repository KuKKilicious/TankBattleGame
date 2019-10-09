// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



}

float ATank::getHealthPercent() const
{
	return static_cast<float>(m_TankHP) / static_cast<float>(m_StartingHealth);
}

bool ATank::AddHealth(float value)
{
	if (FMath::IsNearlyEqual(m_TankHP, m_StartingHealth, 0.001f))
	{
		return false;
	}
	m_TankHP = FMath::Clamp(m_TankHP + static_cast<int>(value), 0, m_StartingHealth);
	return true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	m_TankHP = m_StartingHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	int32  damage = (FMath::Clamp(FPlatformMath::RoundToInt(Damage), 0, m_TankHP));
	m_TankHP -= damage;

	if (m_TankHP <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnDeathBroadcast"));
		onTankDeath.Broadcast();
	}
	return damage;
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

