// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class TANKBATTLEGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATank* getControlledTank() const;
	void BeginPlay() override;

	ATank* getPlayerTank() const;

	virtual void Tick(float DeltaTime)override;

};


