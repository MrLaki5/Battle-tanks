// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	if (!Barrel) {
		return;
	}
	//Vector in which direction should be barrel facing to hit the HitLocation multiplied with speed (definition of Velocity)
	FVector OutLaunchVilocity;
	//Current position of barrel
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Calculate lower hyperbolic trajectory for hitting the HitLocation with starting speed of LaunchSpeed 
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVilocity, StartLocation, HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		//Vector we got from calculating has velocity in it, so we need to normalize it (take down its length to 1 (unit vector))
		auto AimDirection = OutLaunchVilocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
	Barrel->Elevate(5);
}
	

