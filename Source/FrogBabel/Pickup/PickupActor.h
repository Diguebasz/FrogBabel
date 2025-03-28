// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCoinPickupDelgate);

// This prevents us from needing to import headers hear which makes recompiles faster in
// larger projects since headers are not changing.
class USphereComponent;
class URotatingMovementComponent;
class UNiagaraSystem;

UCLASS()
class FROGBABEL_API APickupActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BLueprintAssignable, Category = "YouTube Demo")
	FOnCoinPickupDelgate OnCoinPickup;

	APickupActor();

	// UFUNCTION() is required if the method is being bound to a Delegate
	UFUNCTION()
	void OnBeginOverlapComponentEvent(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);

protected:
	// UPROPERTY() Is used to expose values to the Blueprint System
	// EditDefaultsOnly prevents blueprints from changes values at runtime
	// TObjectPtr<ClassName> is the suggested way of writing ClassName* as of Unreal Engine 5
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	// Side of the Collider, the bigger this is the further away from
	// the Coin mesh the player can pick it up
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	float ColliderRadius{ 32.f };

	// Set the speed of rotation in any direction you want
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	FRotator RotationSpeed{ 0.f, 100.f, 0.f };

	// Sound file that was uploaded to play when you pickup the Coin
	// Coin Pickup Sound https://freesound.org/people/ProjectsU012/sounds/341695/
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	TObjectPtr<USoundBase> SoundFile;

	// Change the volume of the Sound Played, default is 50%
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	float VolumeMultiplier{ 0.5f };

	// The Effect to play when the Coin is picked u
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	TObjectPtr<UNiagaraSystem> OnPickupEffect;

	// The amount of (Unreal Units)/CM to offset the effect when played
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	float PickupEffectSpawnOffset{ 90.f };

	// Even if you are not exposing a Pointer to blueprints we should always set UPROPERTY() so
	// They are properly handled throughout the life of the property
	UPROPERTY()
	TObjectPtr<USphereComponent> ColliderComponent;

	UPROPERTY()
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

	// Because this is not an Pointer we don't need the UPROPERTY() decorator
	FVector Offset;
	FVector Location;
};