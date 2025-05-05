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
#include "Components/SkeletalMeshComponent.h"
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
    
    // The mesh to represent the jump pad.
    SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(RootComponent);

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
            // Obtain the player's current world location.
            FVector PlayerWorldLocation = Character->GetActorLocation();

            // Convert the player's location from world space to BouncePad local space.
            FTransform BouncePadTransform = GetActorTransform();
            FVector LocalPlayerLocation = BouncePadTransform.InverseTransformPosition(PlayerWorldLocation);

            // Adjust the local location:
            // For example, center the player along the local Y axis while preserving the X offset.
            LocalPlayerLocation.X = 0.f;

            // Convert the adjusted local position back to world space.
            FVector AdjustedWorldLocation = BouncePadTransform.TransformPosition(LocalPlayerLocation);

            // Teleport the player.
            // Note: TeleportTo is often preferable to SetActorLocation when the actor has movement components.
            bool bTeleported = Character->TeleportTo(AdjustedWorldLocation, Character->GetActorRotation());

            // Get the center location of this BouncePad actor. Bruh, how tf can I snap the player to the relative center of the object??
            //FVector BouncePadCenter = GetActorLocation() + FVector(0.f, 0.f, 50.f) /* Character->GetActorForwardVector()*/ /* + Character->GetActorLocation()*/;

            //FVector PlayerRelativeLocation = BouncePadCenter * GetComponentTransform().InverseTransformLocation(Character->GetComponentLocation());

            //FVector PlayerRelativeLocation = Character->GetActorLocation() - BouncePadCenter;

            // SetActorLocation (simple repositioning)
            //Character->SetActorLocation(BouncePadCenter, false, nullptr, ETeleportType::TeleportPhysics);

            UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
            MovementComponent->Velocity = FVector::ZeroVector;
            MovementComponent->SetMovementMode(MOVE_Walking);

            FVector LaunchVelocity = LaunchDirection->GetForwardVector() * LaunchStrength;
            Character->LaunchCharacter(LaunchVelocity, true, true);

            OnBounce();
        }
    }
}




/*
UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
MovementComponent->Velocity = FVector::ZeroVector;
MovementComponent->SetMovementMode(MOVE_Walking);*/