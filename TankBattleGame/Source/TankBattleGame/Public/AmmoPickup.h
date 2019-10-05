// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "AmmoPickup.generated.h"

/**
 *
 */
UCLASS()
class TANKBATTLEGAME_API AAmmoPickup : public APickup
{
	GENERATED_BODY()
		virtual void Tick(float DeltaTime)override;
	AAmmoPickup();
	void BeginPlay()override;
private:
	void RotatePickup(float delta_time, float rotPsec);
	UPROPERTY(EditDefaultsOnly)
		float m_rotDegreePsec = 30.f;
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
