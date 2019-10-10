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

bool ATankAIController::IsInEngageRadius(ATank* player, APawn* thisTank)
{
	if (player && thisTank)
	{
		auto distance = thisTank->GetDistanceTo(player);
		return distance <= m_EngageRadius;
	}
	return false;
}



void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = Cast<ATank>(GetPawn());
	ATank* playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerTank && ControlledTank && IsInEngageRadius(playerTank, ControlledTank)) //engaging
	{
		
		ControlledTank->SetEngaged(true);
		MoveToActor(playerTank, m_MoveAcceptanceRadius);
		m_AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		m_AimingComponent->AimAt(playerTank->GetTargetLocation());

		//if aiming is locked
		if (m_AimingComponent->getFiringStatus() == EFiringStatus::Locked && m_AimingComponent->isPlayerInSight())
		{
			m_AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		//TODO: Subscribe local method to OnDeath
		possessedTank->onTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("ONTANKDEATH AI"));
	auto ControlledTank = Cast <ATank>(GetPawn());
	if (ControlledTank)
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}

