// //KuKKi ©2019


#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "TimerManager.h"

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if(!m_movementEnabled){return;}
	if (!ensure(m_LeftTrack&&m_RightTrack)) { return; }
	m_LeftTrack->setThrottle(Throw);
	m_RightTrack->setThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if(!m_movementEnabled){return;}
	if (!ensure(m_LeftTrack&&m_RightTrack)) { return; }
	m_LeftTrack->setThrottle(Throw);
	m_RightTrack->setThrottle(-Throw);
}

void UTankMovementComponent::disableMovement()
{
	m_movementEnabled = false;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	if(!m_movementEnabled){return;}
	auto tankName = GetOwner()->GetName();
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto moveIntention = MoveVelocity.GetSafeNormal();

	auto forwardValue = FVector::DotProduct(tankForward, moveIntention);
	auto turnValue = FVector::CrossProduct(tankForward, moveIntention);

	IntendMoveForward(forwardValue);
	IntendTurnRight(turnValue.Z);

}

void UTankMovementComponent::Boosting()
{

	FTimerHandle timerHandle;

	m_LeftTrack->setMultiplier(m_BoostMultiplier);
	m_RightTrack->setMultiplier(m_BoostMultiplier);
	GetWorld()->GetTimerManager().SetTimer(timerHandle,this,&UTankMovementComponent::ResetMultiplier,10,true, -0.5f);

}

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	if(!ensure(leftTrack&&rightTrack)){return;}
	m_LeftTrack = leftTrack;
	m_RightTrack = rightTrack;
}

void UTankMovementComponent::ResetMultiplier()
{
	m_LeftTrack->setMultiplier(1.f);
	m_RightTrack->setMultiplier(1.f);
}
