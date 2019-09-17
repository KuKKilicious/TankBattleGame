// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);
	void MoveBarrelTowards(const FVector& vector);
	void AimAt(FVector aimLocation, float firingVelocity);


public:

	UStaticMeshComponent* m_Barrel = nullptr;
};
