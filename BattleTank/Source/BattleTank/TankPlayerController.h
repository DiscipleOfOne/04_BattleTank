// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATankPlayerController(); // Constructor
    virtual void BeginPlay() override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent *AimCompRef);
	
private:
    // Moves the barrel towards the crosshair so a shot can hit where the crosshair intersects the world
    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector &) const;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairXLocation = 0.5f;
    
    UPROPERTY(EditDefaultsOnly)
    float CrossHairYLocation = 0.33333f;
    
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 1000000.0f;
    
    bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection, FVector &LookLocation) const;
    bool GetLookVectorHitLocation(FVector LookDirection, FVector &LookLocation, FVector &HitLocation) const;

    
};
