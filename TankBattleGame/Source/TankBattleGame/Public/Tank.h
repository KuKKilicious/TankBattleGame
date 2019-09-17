// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Public/TankAimingComponent.h"


#include "Tank.generated.h"

UCLASS()
class TANKBATTLEGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	void AimAt(FVector aimLocation);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere,Category =Firing, DisplayName = Velocity)
		float m_FiringVelocity = 50000.f;
};
