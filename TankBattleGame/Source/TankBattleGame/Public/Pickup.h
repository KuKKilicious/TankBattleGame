// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class TANKBATTLEGAME_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual
	//sound effects
	//destroy animations
	//OnPickup()
	
protected:
	FName name;
	float value;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* m_Mesh = nullptr;
};
