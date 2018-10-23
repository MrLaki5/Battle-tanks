// Fill out your copyright notice in the Description page of Project Settings.

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