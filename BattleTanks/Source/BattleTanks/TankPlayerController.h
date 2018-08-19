// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick(float deltaTime) override;

	void AimAtCrosshair();
	bool GetHitLocation(FVector& HitLocation) const;

	bool GetLookDirection( FVector & LookDirection, FVector& CameraWorldLocation) const;
	
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;
	
	UPROPERTY(EditAnywhere)
	float LineTraceMaxRange = 1000000;

	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection, FVector CameraWorldLocation) const;
	

};
