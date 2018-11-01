// Copyright Milan Lazarevic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	//Return current health as a precentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category="Health")
	float getHealthPercent() const;

	// Sets default values for this pawn's properties
	ATank();

	//Called by engine when actor damage is dealt
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	FTankDelegate OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category= "Setup")
		int32 StartingHealth=100;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth ; //Initialized in begin play
};
