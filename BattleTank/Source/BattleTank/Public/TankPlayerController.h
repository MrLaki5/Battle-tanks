// Copyright Milan Lazarevic

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;

/**
 * Responsible for helping player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
private:
	//Start the thank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	//Return OUT parameter, true if landscape
	bool GetSightRayHitlocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
};
