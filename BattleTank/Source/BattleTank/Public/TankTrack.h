// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track s used to set maximum driving force and to move the tank and to apply forces to the tank.
 */
UCLASS(meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetThrottle(float Throttle);
	
    // This is max force per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000.0f; // This is in newtons for a 40 ton tank 1G of acceleration
	
private:
    UTankTrack();
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


};
