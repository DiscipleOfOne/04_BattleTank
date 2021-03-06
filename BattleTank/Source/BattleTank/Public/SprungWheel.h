// Copyright Trimble Tech

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    
private:
    // Components
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* MassAxleConstraint = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Axle = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Wheel = nullptr;
    
    void SetupConstraint();
};
