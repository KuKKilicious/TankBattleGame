// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"
class ATank;
class UTankAimingComponent;
/**
 *
 */
UCLASS()
class TANKBATTLEGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	void BeginPlay() override;


	virtual void Tick(float DeltaTime)override;

	UPROPERTY(EditAnywhere)
		float m_MoveAcceptanceRadius = 15000.f;

	void SetPawn(APawn* InPawn) override;
	UTankAimingComponent* m_AimingComponent = nullptr;
	UFUNCTION()
	void OnTankDeath();
};


