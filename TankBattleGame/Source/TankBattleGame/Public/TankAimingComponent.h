// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//enum
UENUM()
enum class EFiringStatus : uint8 {
	Locked, Aiming, Reloading
};

//fwd
class UTankBarrel;
class UTankTurret;
class AProjectile;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveTowards(const FVector& vector);
	void AimAt(FVector aimLocation);
	UFUNCTION(BlueprintCallable)
		void Fire();
	 void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
	void BeginPlay() override;
protected:
	UFUNCTION(BlueprintCallable)
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus firingStatus = EFiringStatus::Reloading;

private:
	UPROPERTY(EditDefaultsOnly, Category = Firing, DisplayName = Velocity)
		float m_FiringVelocity = 10000.f;
	UPROPERTY(EditDefaultsOnly, Category = Firing, DisplayName = ReloadTime)
		float m_ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> m_Projectile;

	UTankBarrel* m_Barrel = nullptr;
	UTankTurret* m_Turret = nullptr;

	float m_ElevationDegreesPerSecond = 1.f;
	double m_LastFireTime = 0;
};
