// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

APawn* ATankAIController::GetControllerTank() const{
	return GetPawn();
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

APawn* ATankAIController::GetPlayerTank() const {
	return GetWorld()->GetFirstPlayerController()->GetPawn();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	MoveToActor(GetPlayerTank(), AcceptanceRadius);

	AimAtUser();
	FireAtUser();
}

void ATankAIController::AimAtUser(){
	if (!ensure(GetPlayerTank() && GetControllerTank())) {
		return;
	}
	auto HitPlace = GetPlayerTank()->GetActorLocation();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}
	AimingComponent->AimAt(HitPlace);
}

void ATankAIController::FireAtUser() {
	if (!ensure(GetPlayerTank() && GetControllerTank())) {
		return;
	}
	auto AimingComponent = GetControllerTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) {
		return;
	}
	AimingComponent->Fire();
}