// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning, TEXT("calling AI TICK"));
	m_ControlledTank = Cast<ATank>(GetPawn());	
	m_AimingComponent = m_ControlledTank->FindComponentByClass<UTankAimingComponent>();
	if (!m_AimingComponent)
	{
		UE_LOG(LogTemp,Warning, TEXT("couldn't find controlled Tank in AI"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_ControlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank && m_ControlledTank)
	{
		MoveToActor(playerTank,m_MoveAcceptanceRadius);
		m_AimingComponent = m_ControlledTank->FindComponentByClass<UTankAimingComponent>();
		m_AimingComponent->AimAt(playerTank->GetTargetLocation());

		m_AimingComponent->Fire();
	}
}

