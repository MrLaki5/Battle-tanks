// Copyright Milan Lazarevic

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	if (!GetPawn()) {
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}


void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) {
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}
	FVector HitLocation;
	if (GetSightRayHitlocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Hit location %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitlocation(FVector& OutHitLocation) const {
	
	int32 ViewPortSizeX, ViewPortSizeY;
	//Gets the size of game screen on monitor
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	//Calculates pixels of white dot from user UI
	FVector2D ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation)) {
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const{
	FVector CameraWorldLocation;
	//Returns vector where is cameras position in the world (CameraWorldPosition) and vector of direction of where is camera looking (OutLookDirection)
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const{
	FHitResult HitResult;
	//Get the start location of line trace
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	//Get the end location of line trace: multiply direction vector with scalar of how far are we watching and add that to our current location (start location)
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	//Line trace, draw line from our location to direction of LookDirection vector in range of 10km and find if there is some object blocking it. If there is return hit coordinates and true, else false.
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Camera)) {
		OutHitLocation.Set(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z);
		return true;
	}
	OutHitLocation.Set(0.0, 0.0, 0.0);
	return false;
}

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
	}
}

void ATankPlayerController::OnPossesedTankDeath() {
	StartSpectatingOnly();
}