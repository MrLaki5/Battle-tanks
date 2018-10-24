// Copyright Milan Lazarevic

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet) {
	if (!leftTrackToSet || !rightTrackToSet) {
		return;
	}

	LeftTrack = leftTrackToSet;
	RightTrack = rightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if(!LeftTrack || !RightTrack){
		return;
	}
	LeftTrack->setThrottle(Throw);
	RightTrack->setThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) {
		return;
	}
	LeftTrack->setThrottle(Throw);
	RightTrack->setThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//Gets direction (unit vector) of tanks current position
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	//Gets direction (unit vector) of where tank should go
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	//skalar mull of vectors to get cos angle which show direction of x 
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	//vector mull of vectors to get uit vector which shows when to turn right or left (if vectors that are mulled are paralel the result will be 0... we use Z component coz thats the P of boject created by mulling vectors)
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	IntendTurnRight(RightThrow);
	IntendMoveForward(ForwardThrow);
}