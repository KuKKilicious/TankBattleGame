// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class TANKBATTLEGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	//-1 max down +1 max up
	void Elevate(float relativeSpeed);
	UPROPERTY(BlueprintReadWrite, Category = MovementSetup)
		float m_MaxDegreesPerSecond = 5;
	UPROPERTY(BlueprintReadWrite, Category = MovementSetup)
		float m_MaxElevation = 50;
	UPROPERTY(BlueprintReadWrite, Category = MovementSetup)
		float m_MinimumElevation = 0;
protected:

};
