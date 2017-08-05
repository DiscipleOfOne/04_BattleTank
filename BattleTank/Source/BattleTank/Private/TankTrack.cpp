// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
    // Work out the required acceleration this frame to correct
    // Calculate and apply sideways force
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
    TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{

    // TODO Clamp Throttle So player can't speed up tank
    Throttle = FMath::Clamp(Throttle, -1.0f, 1.0f);

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Error,TEXT("HIT HAS BEEN EXPERIENCED"))
}


