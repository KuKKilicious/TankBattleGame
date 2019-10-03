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
	void BeginPlay() override;
	void DriveTrack(float ForceToApply);
	UFUNCTION(BlueprintCallable,Category = Input)
	void setThrottle(float Throttle);
	virtual void OnRegister() override;
	//Force that is getting applied to track in Newton
	UPROPERTY(BlueprintReadWrite,Category = Movement)
	float m_TrackMaxDrivingForce = 1000000.f;
private:
	
	TArray <class ASprungWheel*> GetWheels() const;
};
