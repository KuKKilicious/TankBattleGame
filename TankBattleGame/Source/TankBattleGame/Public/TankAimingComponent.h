// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	void MoveTowards(const FVector& vector);
	void AimAt(FVector aimLocation, float firingVelocity);


public:

	UTankBarrel* m_Barrel = nullptr;
	UTankTurret* m_Turret = nullptr;
private:

	float m_ElevationDegreesPerSecond = 1.f;
};
