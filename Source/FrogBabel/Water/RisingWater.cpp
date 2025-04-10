// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogBabel/Water/RisingWater.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

// Sets default values
ARisingWater::ARisingWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    lifetime = 12.5f;
    RiseSpeed = 150.0f;
}

// Called when the game starts or when spawned
void ARisingWater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARisingWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//void AddActorWorldOffset(FVector DeltaLocation()); // I think I need to change this at the end of a line, and not run it as a void.

    // Increase the lifetime counter by the time passed since last tick
    lifetime += DeltaTime;

    // Compute the current upward velocity (assuming constant acceleration)
    float CurrentVelocity = RiseSpeed * (lifetime * 0.05);

    // Compute how far to move in this frame
    float DeltaZ = CurrentVelocity * DeltaTime;

    // Get the current actor location
    FVector CurrentLocation = GetActorLocation();

    // Update the Z value
    CurrentLocation.Z += DeltaZ;

    // Set the new location of the actor
    SetActorLocation(CurrentLocation);
}

