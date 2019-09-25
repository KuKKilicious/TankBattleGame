// //KuKKi ©2019


#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::IntendMoveForward(float Throw)
{

	if (!ensure(m_LeftTrack&&m_RightTrack)) { return; }
	m_LeftTrack->setThrottle(Throw);
	auto tankName = GetOwner()->GetName();
	m_RightTrack->setThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(m_LeftTrack&&m_RightTrack)) { return; }
	m_LeftTrack->setThrottle(Throw);
	m_RightTrack->setThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

	auto tankName = GetOwner()->GetName();
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto moveIntention = MoveVelocity.GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("%s calling MOVE"),*tankName);

	auto forwardValue = FVector::DotProduct(tankForward, moveIntention);
	auto turnValue = FVector::CrossProduct(tankForward, moveIntention);

	IntendMoveForward(forwardValue);
	IntendTurnRight(turnValue.Z);

}

void UTankMovementComponent::Initialize(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	if(!ensure(leftTrack&&rightTrack)){return;}
	m_LeftTrack = leftTrack;
	m_RightTrack = rightTrack;
}
