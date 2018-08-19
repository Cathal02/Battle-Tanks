// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Classes/Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (BarrelToSet)
	{
		Barrel = BarrelToSet;
	}
	
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (TurretToSet)
	{
		Turret = TurretToSet;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation, float FiringSpeed)
{
	if (!Barrel) return;
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("Projectile");


	// This BASICALLY give us the rotation we have to be at to shoot a projectile
	// at X speed to hit it's target
	// Changing the Speed will MOST LIKELY only change the YAW
	
	bool bHaveLaunchVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		FiringSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveLaunchVelocity)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
//		UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution found"), Time);
		MoveBarrelTowards(AimDirection);


	} 
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
	//	UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution not found"), Time);
	}

}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
		// Move the barrel the right amount this frame
		// Given the max elevation speed, and the frame time
	if (Barrel)
	{
		Barrel->Elevate(DeltaRotator.Pitch);
	}

	if (Turret)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
		
}