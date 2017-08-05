// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
// Depends on TankMovementComponent Through AI Pathfinding

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto* ControlledTank = GetPawn();
    
    if(!ensure(PlayerTank && ControlledTank)) { return; }
    
    UTankAimingComponent *TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    
    if( ensure(PlayerTank && ControlledTank))
    {
        MoveToActor(PlayerTank, AcceptanceRadius);
        TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
        // ONly Fire If Locked
        if(EFiringState::Locked == TankAimingComponent->GetFiringState())
        {
            TankAimingComponent->Fire();
        }
    }
}
