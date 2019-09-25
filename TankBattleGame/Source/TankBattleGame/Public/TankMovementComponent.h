// //KuKKi ©2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the Tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLEGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);
	UFUNCTION(BlueprintCallable)
	void IntendTurnRight(float Throw);
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
private:
	UFUNCTION(BlueprintCallable)
	void Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack);
	UTankTrack* m_LeftTrack = nullptr;
	UTankTrack* m_RightTrack = nullptr;
};
