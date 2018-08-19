// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Classes/Engine/World.h"
void UTankBarrel::Elevate(float RelativeSpeed)
{
//	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate called @ speed %f"), RelativeSpeed)
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(Elevation, RelativeRotation.Yaw, RelativeRotation.Roll));
}


