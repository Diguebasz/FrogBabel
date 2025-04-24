// Fill out your copyright notice in the Description page of Project Settings.

#include "FrogBabel/Platforms/RisingLogActor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"

ARisingLogActor::ARisingLogActor()
{
    PrimaryActorTick.bCanEverTick = true;                            // enable Tick :contentReference[oaicite:3]{index=3}
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;
}

void ARisingLogActor::BeginPlay()
{
    Super::BeginPlay();
    InitialLocation = GetActorLocation();
    TargetLocation = InitialLocation + FVector(0.f, 0.f, RiseHeight);
    bRising = true;
}

void ARisingLogActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bRising) return;

    // Compute step and new location
    float Step = RiseSpeed * DeltaTime;
    FVector CurrentLoc = GetActorLocation();
    FVector NewLoc = CurrentLoc + FVector(0.f, 0.f, Step);

    // Clamp at target
    if (NewLoc.Z >= TargetLocation.Z)
    {
        NewLoc.Z = TargetLocation.Z;
        bRising = false;
    }

    // Instantly move actor
    SetActorLocation(NewLoc);                                        // move actor :contentReference[oaicite:4]{index=4}
}
