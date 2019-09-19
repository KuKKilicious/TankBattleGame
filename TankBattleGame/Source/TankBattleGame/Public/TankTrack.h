// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category = Input)
	void setThrottle(float value);

	//Force that is getting applied to track in Newton
	UPROPERTY(EditDefaultsOnly,Category = Movement)
	float m_TrackMaxDrivingForce = 1000000.f;
};
