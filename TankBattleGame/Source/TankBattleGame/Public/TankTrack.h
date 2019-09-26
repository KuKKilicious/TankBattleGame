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
	void ApplySidewaysForce();
	void BeginPlay() override;
	void DriveTrack();
	UFUNCTION(BlueprintCallable,Category = Input)
	void setThrottle(float Throttle);
	virtual void OnRegister() override;
	//Force that is getting applied to track in Newton
	UPROPERTY(EditDefaultsOnly,Category = Movement)
	float m_TrackMaxDrivingForce = 1000000.f;
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	float m_CurrentThrottle = 0.f;
};
