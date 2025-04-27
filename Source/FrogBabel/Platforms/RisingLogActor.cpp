// Fill out your copyright notice in the Description page of Project Settings.

#include "FrogBabel/Platforms/RisingLogActor.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TreeActor.h"

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
    //CurrentState = ELogState::Rising;
}

void ARisingLogActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bRising) return;

    /*switch (CurrentState)
    {
    case ELogState::Rising:
    {*/

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

    // Clamp at target
    if (NewLoc.Z >= TargetLocation.Z)
    {
        NewLoc.Z = TargetLocation.Z;
        bRising = false;
    }

    // Instantly move actor
    SetActorLocation(NewLoc);                                        // move actor :contentReference[oaicite:4]{index=4}
}

    // Instantly move actor
    /*SetActorLocation(NewLoc);                                        // move actor :contentReference[oaicite:4]{index=4}

    FVector Cur = GetActorLocation();
    Cur.Z = FMath::Min(Cur.Z + RiseSpeed * DeltaTime, TopLocation.Z);
    SetActorLocation(Cur);
    if (Cur.Z >= TopLocation.Z)
    {
        CurrentState = ELogState::Rotating;
    }
    break;
    }

    case ELogState::Rotating:
    {
        if (RotationTarget)
        {
            // 1) compute axis from log to target
            FVector Axis = (RotationTarget->GetActorLocation() - GetActorLocation()).GetSafeNormal();

            // 2) create a quaternion for this frame’s rotation
            float AngleRad = FMath::DegreesToRadians(RotateSpeed * DeltaTime);       //:contentReference[oaicite:2]{ index = 2 }
            FQuat DeltaQuat(Axis, AngleRad); //: contentReference[oaicite:3]{ index = 3 }

                // 3) apply it in world-space
            AddActorWorldRotation(DeltaQuat); //: contentReference[oaicite:4]{ index = 4 }

                // 4) track how much we’ve spun so far
            AccumulatedRotation += RotateSpeed * DeltaTime;
            if (AccumulatedRotation >= TotalRotateAngle)
            {
                CurrentState = ELogState::Sinking;
            }
        }
        break;
    }

    case ELogState::Sinking:
    {
        // move down and destroy when back at initial depth
        FVector Cur = GetActorLocation();
        Cur.Z = Cur.Z - SinkSpeed * DeltaTime;
        SetActorLocation(Cur);
        if (Cur.Z <= InitialLocation.Z)
        {
            Destroy();                                                             //:contentReference[oaicite:5]{ index = 5 }
        }
        break;
    }
    }*/
//}
