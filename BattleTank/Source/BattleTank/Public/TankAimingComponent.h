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
    Locked,
    OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
    EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTankBarrel *BarrelToSet, UTankTurret* TurretToSet);
    
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float LaunchSpeed = 10000.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float ReloadTimeInSeconds = 3.0f;
    
    float LastFireTime = 0.0f;
    

public:

    void AimAt(FVector WorldSpaceAim);
    
    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    virtual void BeginPlay() override;

    
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    FVector AimDirection = FVector(1.0f);
    
    bool IsBarrelMoving();
    

    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    EFiringState FiringState = EFiringState::Reloading;
    
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    int32 ShotsRemaining = 5;

    void MoveBarrelTowards(FVector AimDirection);
};
