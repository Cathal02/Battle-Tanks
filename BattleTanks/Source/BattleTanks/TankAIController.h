// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	void BeginPlay();
	void Tick(float DeltaTime);
	
};
