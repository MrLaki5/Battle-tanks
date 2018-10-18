// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetControllerTank() const{
	return Cast<ATank>(GetPawn());
}


void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto PlayerTank = this->GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController cant find player tank!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *PlayerTank->GetName());
	}
}

ATank* ATankAIController::GetPlayerTank() const {
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn);
}