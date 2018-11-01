// Copyright Milan Lazarevic

#include "TankTrack.h"
#include "Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
}

void UTankTrack::setThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1.0, 1.0);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//Callculate force in vector
	auto ForceApplied =  CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	if(Wheels.Num()>0){
		UE_LOG(LogTemp, Warning, TEXT("Number of wheels: %i"), Wheels.Num());
		auto ForcePerWheel = ForceApplied / Wheels.Num();
		for (ASprungWheel* Wheel : Wheels) {
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const {
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { 
			continue; 
		}
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SpreungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SpreungWheel) {
			continue;
		}
		ResultArray.Add(SpreungWheel);
	}
	return ResultArray;
}