// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
    Reloading,
    Aiming,
    Locked
};

class UTankBarrel; // Forward Declaration
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    
    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet);

public:	

    void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;

    
    void MoveBarrelTowards(FVector AimDirection);
    
    

};
