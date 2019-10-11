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
protected:
	UPROPERTY(BlueprintReadOnly)
	float m_EngageRadius = 20000.f;
private:
	void BeginPlay() override;


	bool IsInEngageRadius(ATank* player, APawn* thisTank);
	virtual void Tick(float DeltaTime)override;

	bool IsPlayerInSight();

	UPROPERTY(EditAnywhere)
		float m_MoveAcceptanceRadius = 5000.f;

	UTankAimingComponent* m_AimingComponent = nullptr;
	void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnTankDeath();
};


