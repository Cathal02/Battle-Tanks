// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Classes/Engine/World.h"
void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Yaw + ElevationChange;


	SetRelativeRotation(FRotator(RelativeRotation.Pitch, RawNewElevation, RelativeRotation.Roll));
}
