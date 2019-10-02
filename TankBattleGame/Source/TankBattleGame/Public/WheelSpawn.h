// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WheelSpawn.generated.h"

class ASprungWheel;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLEGAME_API UWheelSpawn : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheelSpawn();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void setWheel(UClass* projectile);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor * getSpawnedActor() const;

private:
	UPROPERTY(VisibleAnywhere)
		ASprungWheel* m_SprungWheel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AActor> m_SpawnWheel;

	UPROPERTY()
	AActor* SpawnedActor = nullptr;
};
