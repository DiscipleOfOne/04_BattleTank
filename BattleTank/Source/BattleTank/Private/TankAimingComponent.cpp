// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // 
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
    if(!Barrel){ return; }
    auto *PawnOwner = GetOwner();
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
    FCollisionResponseParams ResponseParam;
    TArray<AActor*> ActorIgnoreList;
    ActorIgnoreList.Add(GetOwner());
    ActorIgnoreList.Add(GetWorld()->GetFirstPlayerController()->GetPawn());

    bool BHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
     this,
     OutLaunchVelocity,
     StartLocation,
     WorldSpaceAim,
     LaunchSpeed,
     false,
     0.0f,
     0.0f,
     ESuggestProjVelocityTraceOption::DoNotTrace,
     FCollisionResponseParams::DefaultResponseParam,
     ActorIgnoreList,
     false
     );

    if(BHaveAimSolution)
    {
        
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        //MoveBarrel
        MoveBarrelTowards(AimDirection);
        // Convert Aim Direction To Rotator That We Can you To Rotate and Elevate Barrel
    }
    else
    {
    }
    
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}


