// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum
UENUM()
enum class EFiringStatus : uint8{
	Locked, Aiming, Reloading
	};

//fwd
class UTankBarrel;
class UTankTurret;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveTowards(const FVector& vector);
	void AimAt(FVector aimLocation, float firingVelocity);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus firingStatus = EFiringStatus::Reloading;
	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:
	UTankBarrel* m_Barrel = nullptr;
	UTankTurret* m_Turret = nullptr;
	float m_ElevationDegreesPerSecond = 1.f;
};
