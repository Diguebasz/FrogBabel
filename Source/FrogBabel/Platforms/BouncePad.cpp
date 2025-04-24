// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "BouncePad.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

#include "BouncePad.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ABouncePad::ABouncePad()
{
    PrimaryActorTick.bCanEverTick = false;

    // The default scene component.
    DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
    RootComponent = DefaultSceneRoot;

    // The collision box.
    OverlapBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapBox"));
    OverlapBox->SetupAttachment(RootComponent);
    OverlapBox->SetCollisionProfileName("OverlapAllDynamic");

    // The mesh to represent the jump pad.
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);

    // Tthe arrow component.
    LaunchDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("LaunchDirection"));
    LaunchDirection->SetupAttachment(RootComponent);
    // Adjust the arrow’s properties if needed (e.g., size, color) in the editor.

    // The default launch strength. One can also adjust this value in the blueprint actor.
    LaunchStrength = 2400.f;

    // Bind the overlap event.
    OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad::OnOverlapBegin);
}

void ABouncePad::BeginPlay()
{
    Super::BeginPlay();
}

void ABouncePad::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor)
    {
        // Check if the overlapping actor is a character.
        ACharacter* Character = Cast<ACharacter>(OtherActor);
        if (Character)
        {
            // Use the forward vector of the LaunchDirection arrow to determine the launch direction,
            // then multiply by LaunchStrength for intensity.
            FVector LaunchVelocity = LaunchDirection->GetForwardVector() * LaunchStrength;
            Character->LaunchCharacter(LaunchVelocity, true, true);

            UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
            MovementComponent->Velocity = FVector::ZeroVector;
            MovementComponent->SetMovementMode(MOVE_Walking);

            OnBounce();
        }
    }
}




/*
UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
MovementComponent->Velocity = FVector::ZeroVector;
MovementComponent->SetMovementMode(MOVE_Walking);*/