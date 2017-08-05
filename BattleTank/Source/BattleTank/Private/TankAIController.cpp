// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    ATank* AITank = Cast<ATank>(GetPawn());
    Super::Tick(DeltaTime);
    if( PlayerTank && AITank)
    {
        MoveToActor(PlayerTank, AcceptanceRadius);
        
        AITank->AimAt(PlayerTank->GetActorLocation());
        AITank->Fire();
    }
}
