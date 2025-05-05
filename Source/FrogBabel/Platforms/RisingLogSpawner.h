// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
//#include "RisingLogActor.h"
#include "RisingLogSpawner.generated.h"

class ARisingLogActor;

UCLASS()
class FROGBABEL_API ARisingLogSpawner : public AActor
{
    GENERATED_BODY()

public:
    ARisingLogSpawner();

    UFUNCTION(BlueprintImplementableEvent, Category = "Events")
    void OnSpawn();

protected:
    virtual void BeginPlay() override;

private:
    // Collision box to detect the player
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerVolume;                                  // box collision :contentReference[oaicite:5]{index=5}

    // Which platform class to spawn
    UPROPERTY(EditAnywhere, Category = "Spawning")
    TSubclassOf<ARisingLogActor> PlatformClass;                     // spawn class :contentReference[oaicite:6]{index=6}

    // World location where the platform should appear
    UPROPERTY(EditAnywhere, Category = "Spawning")
    FVector SpawnLocation;

    // Called when something overlaps TriggerVolume
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
