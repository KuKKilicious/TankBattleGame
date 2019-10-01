//KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * Looking and Aiming 
 */
class ATank;
UCLASS()
class TANKBATTLEGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime)override;
protected:
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimingComponent);
private:
	bool getLookVectorHitLocation(FVector& hitLocation, const FVector& lookDirection) const;
	bool getSightRayHitLocation(FVector& vector)const;
	void AimTowardsCrosshair();
	bool getLookDirection(FVector2D screenLocation, FVector& LookDirection) const;
private:
	UPROPERTY(EditAnywhere)
		float m_CrosshairXLocation =0.5f;
	UPROPERTY(EditAnywhere)
		float m_CrosshairYLocation = 0.333333f;
	UPROPERTY(EditAnywhere)
		float m_LineTraceRange = 1000000.0f;//in cm
	UTankAimingComponent* m_AimingComponent = nullptr;
	void SetPawn(APawn* InPawn) override;
	UFUNCTION()
		void OnTankDeath();
};
