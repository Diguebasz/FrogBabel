// Fill out your copyright notice in the Description page of Project Settings.

#include "FrogBabel/Platforms/RisingLogActor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TreeActor.h"

ARisingLogActor::ARisingLogActor()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and set a mesh component as the root
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    // Optional: adjust collision, shadows, etc. here
}

void ARisingLogActor::BeginPlay()
{
    Super::BeginPlay();

    OriginLocation = GetActorLocation();
    ElapsedTime = 0.f;
    CurrentState = ERiseSinkState::Rising;

    TArray<AActor*> Found;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        ATreeActor::StaticClass(),
        Found);

    if (Found.Num() > 0)
    {
        TreeActor = Cast<ATreeActor>(Found[0]);
    }


    if (!TreeActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has no TargetActor!"), *GetName());
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("%s targeting %s"),
            *GetName(), *TreeActor->GetName());
    }
}

void ARisingLogActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    switch (CurrentState)
    {
    case ERiseSinkState::Rising:
        HandleRising(DeltaTime);
        break;

    case ERiseSinkState::Sinking:
        HandleSinking(DeltaTime);
        break;

    case ERiseSinkState::Finished:
        // Once finished, simply queue for destroy
        Destroy();
        break;
    }
}

void ARisingLogActor::HandleRising(float DeltaTime)
{
    ElapsedTime += DeltaTime;
    const float Alpha = FMath::Clamp(ElapsedTime / (RiseDuration+(ElapsedTime/5)), 0.f, 1.f);

    // Interpolate Z from OriginLocation.Z to OriginLocation.Z + RiseHeight
    FVector NewLoc = OriginLocation;
    NewLoc.Z += Alpha * RiseHeight;
    SetActorLocation(NewLoc);

    if (Alpha >= 1.f)
    {
        // switch to sinking
        CurrentState = ERiseSinkState::Sinking;
        ElapsedTime = 0.f;
    }
}

void ARisingLogActor::HandleSinking(float DeltaTime)
{
    // Advance time
    ElapsedTime += DeltaTime;

    // Raw progress 0→1 over SinkDuration
    const float RawAlpha = FMath::Clamp(ElapsedTime / SinkDuration, 0.f, 1.f);
    // Smooth it with an ease-in-out (exponent 2.0)
    const float SmoothAlpha = FMath::InterpEaseInOut(0.f, 1.f, RawAlpha, 2.f);

    // 1) Move down (but eased)
    {
        FVector NewLoc = OriginLocation;
        NewLoc.Z += (1.f - SmoothAlpha) * RiseHeight;
        SetActorLocation(NewLoc);
    }

    // 2) Tilt to the side relative to TargetActor (eased)
    if (TreeActor)
    {
        // Flattened "away" vector
        FVector Away = GetActorLocation() - TreeActor->GetActorLocation();
        Away.Z = 0.f;
        Away.Normalize();
        if (!Away.IsNearlyZero())
        {
            // Side direction = Up × Away
            FVector SideDir = FVector::CrossProduct(FVector::UpVector, Away).GetSafeNormal();
            // Axis to rotate around = Up × SideDir
            FVector RotAxis = FVector::CrossProduct(FVector::UpVector, SideDir).GetSafeNormal();

            // Build quaternion from 0→90° based on eased alpha
            const float AngleRad = FMath::DegreesToRadians(-60.f * SmoothAlpha);
            FQuat FallQuat(RotAxis, AngleRad);
            FQuat NewQuat = FQuat::Slerp(FQuat::Identity, FallQuat, SmoothAlpha);

            // Apply it to your mesh (or root, if appropriate)
            MeshComp->SetRelativeRotation(NewQuat);
        }
    }

    // 3) Once raw α hits 1, we’re fully sunk/tilted—destroy immediately
    if (RawAlpha >= 1.f)
    {
        Destroy();
    }
}