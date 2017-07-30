// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

// Sets default values
ATankPlayerController::ATankPlayerController()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
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
}



void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("Tick Tick Motherfucker"))
}




ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return;}
    //GetWorld Location Through Crosshair
    // If it hits something
    // Move the barrel so it can hit it
}
