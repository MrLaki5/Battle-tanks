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
	Locked,
	OutOfAmmo
};

//Forward declaration
class UTankBarrel;	
class UTankTurret;
class AProjectile;

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
		EFireState FireState = EFireState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; // 40m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBP = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void Fire();

	EFireState GetFireState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetRoundsLeft();

private:
	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	void MoveBarrel(FVector AimDirection);

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void BeginPlay() override;

	bool IsBarrelMoving();

	FVector AimDirection;

	int RoundsLeft = 3;
};
