// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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
	ATank* GetControllerTank() const;
	ATank* GetPlayerTank() const;
	void AimAtUser();
	void FireAtUser();

	//How close can AI tank get
	float AcceptanceRadius = 3000; //in cm
};
