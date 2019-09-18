// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();


	auto controlledTank = getControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI TANK, name: %s"), *controlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("couldn't find controlled Tank"));
	}
	auto playerTank = getPlayerTank();

	if (playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player TANK found, name: %s"), *playerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("couldn't find playerTank"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//getControlledTank()->AimAt(getPlayerTank()->GetTargetLocation());
}

ATank* ATankAIController::getPlayerTank() const
{
	auto playerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	return Cast<ATank>(playerController);
}


ATank* ATankAIController::getControlledTank() const
{

	 return Cast<ATank>(GetPawn());
}

