// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class UProjectileMovementComponent;

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
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

};
