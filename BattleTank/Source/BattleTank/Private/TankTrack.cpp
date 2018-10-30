// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	//calculate the slippage speed, skalar mul of vectors in 90 degrees gives 0 and of parallel vectors value because of cos
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work required acceleration (speed over time) this frame to correct, speed/time devided with right vec value with - so that it goes in oposite direction
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());
	//Calculate side ways friction
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//Devide by two because of 2 tracks
	auto CorrectionForce = (TankRoot->GetMass()* CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::setThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1.0);
}

void UTankTrack::DriveTrack()
{
	//Callculate force in vector
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	//Find location where force is applied
	auto ForceLocation = GetComponentLocation();
	//Find tank body to which is force applied
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//Apply force
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
