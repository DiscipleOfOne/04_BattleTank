// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();

    if(ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Tank Controller Has Possessed: %s"), *(ControlledTank->GetName()))
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AI Tank Controller Hasn't possesed anything"))
    }
    
}


ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


