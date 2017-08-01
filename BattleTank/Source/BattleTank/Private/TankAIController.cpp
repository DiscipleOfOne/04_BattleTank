// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();

    if(PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("I've found the player tank: %s"), *(PlayerTank->GetName()))
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AI Tank Controller Hasn't Foudn the Player Controller"))
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    ATank* PlayerTank = GetPlayerTank();
    ATank* AITank = GetControlledTank();
    Super::Tick(DeltaTime);
    if( PlayerTank && AITank)
    {   //
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}



ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}



ATank* ATankAIController::GetPlayerTank() const
{
    auto *PlayerPawn =  GetWorld()->GetFirstPlayerController()->GetPawn();
    if(PlayerPawn)
    {
        return Cast<ATank>(PlayerPawn);
    }
    else
    {
        return nullptr;
    }
}

