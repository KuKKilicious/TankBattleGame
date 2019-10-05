// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class AHealthPickup : public APickup
{
	GENERATED_BODY()
		void BeginPlay() override;
	AHealthPickup();
	virtual void Tick(float DeltaTime)override ;
private:
	void RotatePickup(float delta_time, float rotPsec);

	UPROPERTY(EditDefaultsOnly)
	float m_rotDegreePsec =30.f;
	UFUNCTION()
	void OnOverlap( UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
