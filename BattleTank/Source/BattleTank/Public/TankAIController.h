// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    
private:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	
    UPROPERTY(EditAnywhere, Category = "Setup")
    float AcceptanceRadius = 5000.0f; // How Close Will The AI Tank Try to get
	
    
    UFUNCTION()
    void OnPossessedTankDeath();
    
    virtual void SetPawn( APawn *InPawn) override;
};
