// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	APawn* GetControllerTank() const;
	APawn* GetPlayerTank() const;
	void AimAtUser();
	void FireAtUser();

	//How close can AI tank get
	float AcceptanceRadius = 3000; //in cm
};
