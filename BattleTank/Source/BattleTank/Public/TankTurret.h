// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:

	//-1 is max left speed, and +1 is max right speed
	void Rotate(float RelativeSpeed);

	UPROPERTY(EditAnywhere)
		float MaxDegreesPerSecond = 25;
	
};
