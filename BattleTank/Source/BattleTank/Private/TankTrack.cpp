// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::setThrottle(float Throttle) {
	//Callculate force in vector
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	//Find location where force is applied
	auto ForceLocation = GetComponentLocation();
	//Find tank body to which is force applied
	auto TankRoot =Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Apply force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}