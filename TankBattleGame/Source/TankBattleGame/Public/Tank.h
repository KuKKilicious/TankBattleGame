// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class TANKBATTLEGAME_API ATank : public APawn
{
	GENERATED_BODY()
public:
	FTankDelegate onTankDeath;
	// Sets default values for this pawn's properties
	ATank();
	//returns health between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float getHealthPercent() const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(BlueprintReadWrite)
	int32 m_StartingHealth = 100;
private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere)
		int32 m_TankHP = 100;


};
