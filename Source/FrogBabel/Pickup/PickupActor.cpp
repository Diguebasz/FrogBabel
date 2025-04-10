// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "NiagaraFunctionLibrary.h" // Ignore the Niagara errors, apparently this is a bug in visual studio.

// Sets default values
APickupActor::APickupActor()
{
	// Tick is not need so we should turn it off
	PrimaryActorTick.bCanEverTick = false;

	// The default scene component.
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	RootComponent = DefaultSceneRoot;

	// Setup Collider
	ColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("ColliderComponent");

	// Set to Root Component since all things start at the collider
	//SetRootComponent(DefaultSceneRoot);

	ColliderComponent->SetupAttachment(RootComponent);
	ColliderComponent->SetCapsuleRadius(ColliderRadius);

	ColliderComponent->InitCapsuleSize(64.f, 200.f); // Adjust for desired shape

	// Set default rotation (rotates the capsule 90 degrees around Y-axis so that the long side is horizontal)
	CapsuleRelativeRotation = FRotator(0.f, 0.f, 90.f);

	ColliderComponent->SetRelativeRotation(CapsuleRelativeRotation);

	// We want overlap events to be generated
	ColliderComponent->SetGenerateOverlapEvents(true);

	// QueryOnly is all that is required for overlap events to be triggered
	ColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Since we only want to trigger on player we can ignore everything that isn't a Pawn
	ColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	ColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Setup OnBeginOverlap Event
	ColliderComponent->OnComponentBeginOverlap.AddDynamic(
		this, &APickupActor::OnBeginOverlapComponentEvent
	);

	// Static Mesh is required so the user can see the Coin
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	// Attach to Collider component so it is always in the center
	MeshComponent->SetupAttachment(RootComponent);

	// This does not required collisions so we disable for everything and ignore on everything
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Don't want this to generate overlap events so we disable it
	MeshComponent->SetGenerateOverlapEvents(false);

	// Setup a rotation component so the Coin spins
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(
		"RotatingMovementComponent"
	);
	// Add rotation speed based on users Input
	RotatingMovementComponent->RotationRate = RotationSpeed;

	// Pre compute the Offset - This will make startup slower but pick up faster
	Offset = GetActorUpVector() * FVector(0, 0, PickupEffectSpawnOffset);

	// This object is static so it will never leave the current location so we will cache it
	Location = GetActorLocation();
}

void APickupActor::OnBeginOverlapComponentEvent(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
)
{
	

	// Using Cast to check if the OtherActor is a Character
	// This should be changed if you have AI walking around
	
	if (Cast<APawn>(OtherActor)) {

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		
		if (OtherActor == PlayerController->GetPawn()) {
			OnPickup();
			// Check if SoundFile is set before attempting to use it
			if (SoundFile)
			{
				// Play the provided sound file here
				UGameplayStatics::PlaySoundAtLocation(
					this, SoundFile, Location, VolumeMultiplier);
			}

			// Check if PickupEffect is set before attempting to use it
			if (OnPickupEffect)
			{
				// Play the PickupEffect at the Character Actors Location with the provided Offset
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(
					GetWorld(), OnPickupEffect, OtherActor->GetActorLocation() + Offset
				);
			}

			if (OnCoinPickup.IsBound())
			{
				OnCoinPickup.Broadcast();
			}

			// Destroy the Actor so it disappears from the world
			Destroy();
		}

	}
	
}