// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	UTankTrack();

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	//Sets Throttle from -1 to 1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void setThrottle(float Throttle);

	//Max force per track, in Newtons (mass * acceleration)
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000; //400000 = 40000kg *10cm/s2 *100 (conver cm to m)
	
};
