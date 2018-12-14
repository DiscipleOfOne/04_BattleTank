// Copyright Trimble Tech

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
    SetRootComponent(MassAxleConstraint);

    Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
    Axle->SetupAttachment(MassAxleConstraint);

    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
    AxleWheelConstraint->SetupAttachment(Axle);

    Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
    Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
    
    SetupConstraint();
    
}

void ASprungWheel::SetupConstraint()
{
    if(GetAttachParentActor())
    {
        UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
        if(!BodyRoot) { return; }
        // First Constraint Setup BodyRoot -> Axle
        MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
        
        // Second Constraint Setup Axle -> Wheel
        AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None,  Wheel, NAME_None);
        
    }
}


// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

