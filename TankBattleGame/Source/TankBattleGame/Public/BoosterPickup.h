// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BoosterPickup.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLEGAME_API ABoosterPickup : public APickup
{
	GENERATED_BODY()
	ABoosterPickup();
	void BeginPlay() override;
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	void Tick(float DeltaTime) override;
	void RotatePickup(float delta_time, float rotPsec);
	UPROPERTY(EditDefaultsOnly)
	float m_rotDegreePsec = 30.f;
};
