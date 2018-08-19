// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
#include "Tank.h"
 #include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* tank = GetControlledTank();
	if (!tank)
	{
		UE_LOG(LogTemp, Error, TEXT("No Tank found"));
		
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController found tank: %s!"), *tank->GetName());

	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank())  return;

	FVector HitLocation; // Out paramater
	GetHitLocation(HitLocation); // Side-Affect - Will change HitLocation

}



bool ATankPlayerController::GetHitLocation(FVector& HitLocation) const
{
	if (GetWorld())
	{

		// Gets our look direction
		FVector LookDirection;
		FVector CameraWorldLocation;

		if (GetLookDirection(LookDirection, CameraWorldLocation))
		{

			// Checks to see if our linetrace hits anything
			if (GetLookVectorHitLocation(HitLocation, LookDirection, CameraWorldLocation))
			{

				// Tells the tank we are controlling to aim at this hit location
				GetControlledTank()->AimAt(HitLocation);
			}

		}

	}

	return false;
	
}

// Gets the direction we are looking in according to the crosshair
bool ATankPlayerController::GetLookDirection(FVector& LookDirection, FVector& CameraWorldLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Gets the Screenlocation where the crosshair is 
	FVector2D Screenlocation = FVector2D(
		ViewportSizeX * CrosshairXLocation, 
		ViewportSizeY * CrossHairYLocation);

	// Deproject the screen position of the crosshair to a world direction


	// Turns the crosshair point to a world coord;
	return DeprojectScreenPositionToWorld(
		Screenlocation.X, 
		Screenlocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}


// Returns the location of the point we hit with our line trace
bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection, FVector CameraWorldLocation) const
{

	// Setup variables for linetrace
	FVector StartLocation = CameraWorldLocation;
	FVector EndLocation = StartLocation + (LookDirection * LineTraceMaxRange);
	FHitResult HitResult;

	
	// Line trace to see if we hit landscape
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility);

	auto Time = GetWorld()->GetTimeSeconds();
	if (HitResult.bBlockingHit) {
		HitLocation = HitResult.Location;
		return true;
	} 


	HitLocation = FVector(0);
	return false;
}
