// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetPawn();
	m_AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!m_AimingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("couldn't find controlled Tank in AI"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank && ControlledTank)
	{
		MoveToActor(playerTank, m_MoveAcceptanceRadius);
		m_AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		m_AimingComponent->AimAt(playerTank->GetTargetLocation());

		//if aiming is locked
		if (m_AimingComponent->getFiringStatus() == EFiringStatus::Locked)
		{
			m_AimingComponent->Fire();
		}
	}
}

