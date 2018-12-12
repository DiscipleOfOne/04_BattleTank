// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
private:
    // Sets default values for this pawn's properties
    ATank();
    
    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 StartingHealth = 100;

    UPROPERTY(VisibleAnywhere, Category = "Health")
    int32 CurrentHealth = StartingHealth;
    
public:
    virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser);
    
    // Returns current health as a percentage of starting health between 0 and 1
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

};
