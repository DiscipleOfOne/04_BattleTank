// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
    if(!Barrel){ return; }
    auto *PawnOwner = GetOwner();
    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
    FCollisionResponseParams ResponseParam;
    bool BHaveAimSolution =UGameplayStatics::SuggestProjectileVelocity
    (
     this,
     OutLaunchVelocity,
     StartLocation,
     WorldSpaceAim,
     LaunchSpeed,
     ESuggestProjVelocityTraceOption::DoNotTrace
     );
    
    if(BHaveAimSolution)
    {
        
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        //MoveBarrel
        MoveBarrelTowards(AimDirection);
        
        // Convert Aim Direction To Rotator That We Can you To Rotate and Elevate Barrel
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DletaRotator = AimAsRotator - BarrelRotator;
    Barrel->ElevateBarrel(5); // TODO Remove MAgic Number
    UE_LOG(LogTemp, Error, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())
}


