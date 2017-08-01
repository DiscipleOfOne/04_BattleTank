// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"




void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    
    auto Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    
    SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
    
}
