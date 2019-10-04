// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class TANKBATTLEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float speed);
private:

	UPROPERTY(EditDefaultsOnly = "Setup")
		float m_DestroyDelay = 5.f;
	UPROPERTY(EditDefaultsOnly,Category = "Setup")
		float m_ProjectileDamage = 5.f;
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjectileCollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ProjectileLaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ProjectileImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
		URadialForceComponent* ProjectileExplosionForce = nullptr;
	void PrintParams();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse, const FHitResult& Hit);
	void OnTimerExpire();
};
