// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet)
{
    Barrel = BarrelToSet;
    Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
        if(ShotsRemaining <= 0)
        {
            FiringState = EFiringState::OutOfAmmo;
        }
        else if((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
        {
            FiringState = EFiringState::Reloading;
        }
        else if (IsBarrelMoving())
        {
            FiringState = EFiringState::Aiming;
        }
        else
        {
            FiringState = EFiringState::Locked;
        }
}


bool UTankAimingComponent::IsBarrelMoving()
{
    if(!ensure(Barrel)) { return false; }
    auto BarrelForward = Barrel->GetForwardVector();
    return !BarrelForward.Equals(AimDirection, 0.01f);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
    return FiringState;
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
    if(!ensure(Barrel)){ return; }
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
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    if(!ensure(Barrel && Turret)) { return; }
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    
    if(FMath::Abs(DeltaRotator.Yaw) < 180)
    {
        Turret->Rotate(DeltaRotator.Yaw);
    }
    else
    {
        Turret->Rotate(-DeltaRotator.Yaw);
    }

}

void UTankAimingComponent::Fire()
{
    if(FiringState != EFiringState::Reloading && FiringState != EFiringState::OutOfAmmo)
    {
        if(!ensure(ProjectileBlueprint)) { return; }
        if(!ensure(Barrel)) { return; }
        FVector StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
        auto BarrelRotator = Barrel->GetForwardVector().Rotation();
        auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, StartLocation, BarrelRotator);
        Projectile->LaunchProjectile(LaunchSpeed);
        LastFireTime = GetWorld()->GetTimeSeconds();
        ShotsRemaining --;
    }
}




