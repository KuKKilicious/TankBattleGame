// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(!GetPawn()){UE_LOG(LogTemp,Error,TEXT("NO PAWN"));return;}

	m_AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(m_AimingComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("calling found AIMING COMPONENT"))
		FoundAimingComponent(m_AimingComponent);
		
	}else
	{
		UE_LOG(LogTemp,Warning,TEXT("COULDN'T FIND AIMING COMPONENT")) 
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}



void ATankPlayerController::AimTowardsCrosshair()
{
	if(!GetPawn()){return;}
	m_AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(m_AimingComponent)) { return; } 

	FVector HitLocation; //Out param
	if (getSightRayHitLocation(HitLocation))
	{
	// get world location of linetrace through crosshair hits something
	//if it hits the landscape
		//aim to the point
		m_AimingComponent->AimAt(HitLocation);
	}

}

bool  ATankPlayerController::getSightRayHitLocation(FVector& hitLocation) const
{
	

	FHitResult outHit;

	//find crosshair pos
	int32 viewportSizeX, viewportSizeY;
	GetViewportSize(viewportSizeX,viewportSizeY);

	FVector2D screenLocation (viewportSizeX *m_CrosshairXLocation,viewportSizeY*m_CrosshairYLocation);
	FVector lookDirection;
	//deproject crosshair pos to world direction
	if(getLookDirection(screenLocation,lookDirection))
	{
		return getLookVectorHitLocation(hitLocation,lookDirection);
	}
	hitLocation = FVector(0.f, 0.f, 0.f);
	return false;
}

bool ATankPlayerController::getLookVectorHitLocation(FVector& hitLocation, const FVector& lookDirection) const
{
	FHitResult hit;
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector Endpoint (cameraLocation+(lookDirection *m_LineTraceRange));
	
	if(GetWorld()->LineTraceSingleByChannel(hit,cameraLocation,Endpoint,ECC_Camera))
	{
		hitLocation = hit.Location;
		auto TankName = GetName();
		return true;
	}else
	{
		hitLocation = FVector(0);
		return false;
	}
}
//deproject crosshair pos to world direction out param @FVector lookDirection
bool ATankPlayerController::getLookDirection(FVector2D screenLocation, FVector& LookDirection) const
{
	FVector worldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, LookDirection);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto possessedTank = Cast<ATank>(InPawn);
		if (!ensure(possessedTank)) { return; }
		//TODO: Subscribe local method to OnDeath
		possessedTank->onTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);

	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

