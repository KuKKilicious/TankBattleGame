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

	UPROPERTY(EditDefaultsOnly)
		float m_MoveAcceptanceRadius = 30.f;

	UTankAimingComponent* m_AimingComponent = nullptr;
	ATank* m_ControlledTank = nullptr;
};


