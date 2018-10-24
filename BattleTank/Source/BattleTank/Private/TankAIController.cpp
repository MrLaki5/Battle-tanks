// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetControllerTank() const{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
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
	GetControllerTank()->AimAt(HitPlace);
}

void ATankAIController::FireAtUser() {
	if (!ensure(GetPlayerTank() && GetControllerTank())) {
		return;
	}
	GetControllerTank()->Fire();
}