// Copyright Milan Lazarevic

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enumm for aiming state
UENUM()
enum class EFireState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel;	
class UTankTurret;

//Component used for tank aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFireState FireState = EFireState::Aiming;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; // 400m/s
private:
	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	void MoveBarrel(FVector AimDirection);
};
