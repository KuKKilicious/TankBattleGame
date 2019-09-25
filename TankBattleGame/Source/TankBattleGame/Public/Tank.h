// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
UCLASS()
class TANKBATTLEGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	UFUNCTION(BlueprintCallable)
		void Fire();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	UTankBarrel* m_Barrel = nullptr;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditDefaultsOnly, Category = Firing, DisplayName = Velocity)
		float m_FiringVelocity = 50000.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> m_sphereProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Firing, DisplayName = ReloadTime)
	float m_ReloadTimeInSeconds = 3.f;
	double m_LastFireTime = 0;
};
