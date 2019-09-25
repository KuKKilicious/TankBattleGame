// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* controlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank &&controlledTank)
	{

		MoveToActor(playerTank,m_MoveAcceptanceRadius);

		controlledTank->AimAt(playerTank->GetTargetLocation());

		controlledTank->Fire();
	}
}

