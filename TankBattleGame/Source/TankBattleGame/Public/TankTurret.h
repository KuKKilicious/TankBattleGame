// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Yawing(float relativeYawSpeed);
private:
	UPROPERTY(EditAnywhere, Category = MovementSetup)
		float m_MaxDegreesPerSecond = 20;

};
