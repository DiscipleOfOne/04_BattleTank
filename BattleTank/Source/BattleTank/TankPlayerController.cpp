// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Is Alive"))

    
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Tank is Currently Possesed"))
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("AI Possessed Tank is Called: %S"), *(ControlledTank->GetName()))
    
}
