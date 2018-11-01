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

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
		void OnPossesedTankDeath();

protected:
	//How close can AI tank get
	UPROPERTY(EditDefaultsOnly, Category= "Setup")
	float AcceptanceRadius = 8000; //in cm
};
