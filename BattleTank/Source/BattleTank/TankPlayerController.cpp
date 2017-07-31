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
    AimTowardsCrosshair();
}




ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) {return;}
    
    FVector HitLocation; // Out Parameter
    if(GetSightRayHitLocation(HitLocation)) // True Means It has hit something
    {
        GetControlledTank()->AimAt(HitLocation);
        //UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
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
    if(GetLookDirection(ScreenLocation, LookDirection, LookLocation))
    {
        GetLookVectorHitLocation(LookDirection, LookLocation, HitLocation);
        
    }
    return true;
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
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetControlledTank());
    FCollisionResponseParams ResponseParameters = FCollisionResponseParams();    
    
    if (GetWorld()->LineTraceSingleByChannel
    (
     HitResult,
     LookLocation,
     EndLocation,
     ECC_Visibility,
     TraceParameters,
     ResponseParameters
     ))
    {
        HitLocation = HitResult.Location;
        return true;
    }
    return true;
    
}
