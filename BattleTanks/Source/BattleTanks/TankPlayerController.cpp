// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Classes/Engine/World.h"
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
	if (GetSightRayHitLocation(HitLocation)) // Side-Affect - Will change HitLocation
	{
		//TODO Tell tank to aim at this point
	}
	// Get World Location throgh crosshair (linetrace)
	// If it hits the landscape
		// Tell the controlled thank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	if (GetWorld())
	{
		FVector LookDirection;
		if (GetLookDirection(LookDirection))
		{

		}
		// Line trace along that look direction, and see what we hit

		FVector StartLocation = GetControlledTank()->GetActorTransform().GetLocation();
		FVector EndLocation = StartLocation + FVector(0, 1000, 0);
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
		FHitResult HitResult;


		// Line trace to see if we hit landscape
		GetWorld()->LineTraceSingleByObjectType(HitResult, StartLocation, EndLocation, ECC_WorldStatic, RV_TraceParams);
		
		
		if (HitResult.bBlockingHit)
		{
			// Set the out paramater
			HitLocation = HitResult.Location;
			return true;
		}
	}

	return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector& LookDirection) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Gets the Screenlocation where the crosshair is 
	FVector2D Screenlocation = FVector2D(
		ViewportSizeX * CrosshairXLocation, 
		ViewportSizeY * CrossHairYLocation);

	// Deproject the screen position of the crosshair to a world direction

	FVector CameraWorldLocation; // Will be discarded

	DeprojectScreenPositionToWorld(
		Screenlocation.X, 
		Screenlocation.Y, 
		CameraWorldLocation, 
		LookDirection);
	return true;
}