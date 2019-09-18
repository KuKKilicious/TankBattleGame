// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto controlledTank = getControlledTank();

	if (controlledTank)
	{
		UE_LOG(LogTemp,Warning, TEXT("Tank posessed, name: %s"), *controlledTank->GetName())
	}else
	{
		UE_LOG(LogTemp,Warning, TEXT("couldn't find controlled Tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
ATank* ATankPlayerController::getControlledTank() const
{
	//UE_LOG(LogTemp, Warning, TEXT("controlledTank get"));

	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::getLookVectorHitLocation(FVector& hitLocation, const FVector& lookDirection) const
{
	FHitResult hit;
	FVector cameraLocation = PlayerCameraManager->GetCameraLocation();
	FVector Endpoint (cameraLocation+(lookDirection *m_LineTraceRange));
	
	if(GetWorld()->LineTraceSingleByChannel(hit,cameraLocation,Endpoint,ECC_Visibility))
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

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!getControlledTank()) { return; }

	FVector HitLocation; //Out param
	if (getSightRayHitLocation(HitLocation))
	{
	// get world location of linetrace through crosshair hits something
	//if it hits the landscape
		//aim to the point
		getControlledTank()->AimAt(HitLocation);
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
		if( getLookVectorHitLocation(hitLocation,lookDirection))
		{
			return true;
		}
	}
	hitLocation = FVector(0.f, 0.f, 0.f);
	return false;
}
//deproject crosshair pos to world direction out param @FVector lookDirection
bool ATankPlayerController::getLookDirection(FVector2D screenLocation, FVector& LookDirection) const
{
	FVector worldLocation;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, LookDirection);
}
