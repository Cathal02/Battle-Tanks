// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"






ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("TankAIController.GetPlayerTank(): No PlayerTank found!"));
		return nullptr;

	}
	return PlayerTank;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetPlayerTank();
	if (!tank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank found"));

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController found PlayerTank: %s!"), *tank->GetName());

	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		// TODO: Move towards the player

		// Aim towards the player
		
		// Fire if ready
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	
}
