// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
// Sets default values
ATankPlayerController::ATankPlayerController()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(AimingComponent) {
        FoundAimingComponent(AimingComponent);
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetPawn()) {return;}
    
    FVector HitLocation; // Out Parameter
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(AimingComponent)) {return; }
    
    if(GetSightRayHitLocation(HitLocation)) // True Means It has hit something
    {
        AimingComponent->AimAt(HitLocation);
    }
}


bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
    // Found Crosshair Position In Screen Coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
    
    FVector LookDirection;
    FVector LookLocation;
    if(GetLookDirection(ScreenLocation, LookDirection, LookLocation) && GetLookVectorHitLocation(LookDirection, LookLocation, HitLocation))
    {
        return true;
    }
    return false;
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection, FVector &LookLocation) const
{
    FVector CameraWorldLocation; // To Be Trashed
    
    return DeprojectScreenPositionToWorld
    (
     ScreenLocation.X,
     ScreenLocation.Y,
     LookLocation,
     LookDirection
     );
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &LookLocation, FVector &HitLocation) const
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    FHitResult HitResult;
    FVector EndLocation = LookLocation + (LookDirection * LineTraceRange);
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetPawn());
    FCollisionResponseParams ResponseParameters = FCollisionResponseParams();    
    
    if (GetWorld()->LineTraceSingleByChannel
    (
     HitResult,
     LookLocation,
     EndLocation,
     ECC_Camera ,
     TraceParameters,
     ResponseParameters
     ))
    { // SOMETHING WAS HIT
        
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0.0f);
    return false;
    
}


void ATankPlayerController::SetPawn( APawn *InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank> (InPawn);
        if(!ensure(PossessedTank)) { return; }
        
        PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
}

