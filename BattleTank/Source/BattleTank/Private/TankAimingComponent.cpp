// Copyright Milan Lazarevic

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	//So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {

	if (!ensure(Barrel)) {
		return;
	}
	//Vector in which direction should be barrel facing to hit the HitLocation multiplied with speed (definition of Velocity)
	FVector OutLaunchVilocity;
	//Current position of barrel
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Calculate lower hyperbolic trajectory for hitting the HitLocation with starting speed of LaunchSpeed 
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVilocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		//Vector we got from calculating has velocity in it, so we need to normalize it (take down its length to 1 (unit vector))
		AimDirection = OutLaunchVilocity.GetSafeNormal();
		MoveBarrel(AimDirection);

		auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: ELEVATEEE"), time);
	}
	else {
		auto time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), time);
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) {

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);
	//Always yaw shortest way
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire() {
	if (FireState == EFireState::Locked || FireState==EFireState::Aiming) {

		if (!ensure(Barrel)) {
			return;
		}

		LastFireTime = FPlatformTime::Seconds();

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		if (ensure(Projectile)) {
			Projectile->LaunchProjectile(LaunchSpeed);
			RoundsLeft--;
		}
	}
}

EFireState UTankAimingComponent::GetFireState() const
{
	return FireState;
}

int32 UTankAimingComponent::GetRoundsLeft()
{
	return RoundsLeft;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
	if (RoundsLeft <= 0) {
		FireState = EFireState::OutOfAmmo;
		RoundsLeft = 0;
	}
	else if (isReloaded) {
		FireState = EFireState::Reloading;
	}
	else if(IsBarrelMoving()){
		FireState = EFireState::Aiming;
	}
	else {
		FireState = EFireState::Locked;
	}
}
	
bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) {
		return false;
	}
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); //vectors are equal
}
