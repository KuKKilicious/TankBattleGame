// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"
class UPhysicsConstraintComponent;
class USphereComponent;
UCLASS()
class TANKBATTLEGAME_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void AddDrivingForce(float ForceToApply);
	void ApplyForce();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UFUNCTION()
	void onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UPROPERTY(VisibleAnywhere)
		USphereComponent* m_Wheel = nullptr;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* m_WheelAxle = nullptr;
	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent* m_MassAxleConstraint = nullptr;
	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent* m_AxleWheelConstraint = nullptr;
	float m_totalForceMagnitudeThisFrame = 0.f;
};
