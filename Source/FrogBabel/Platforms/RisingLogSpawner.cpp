// Fill out your copyright notice in the Description page of Project Settings.

#include "FrogBabel/Platforms/RisingLogSpawner.h"
#include "Engine/World.h"
#include "RisingLogActor.h"
#include "GameFramework/Character.h"

//class ARisingLogActor;

ARisingLogSpawner::ARisingLogSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
    TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));  // create box :contentReference[oaicite:7]{index=7}
    RootComponent = TriggerVolume;
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ARisingLogSpawner::OnOverlapBegin);  // bind overlap :contentReference[oaicite:8]{index=8}
}

void ARisingLogSpawner::BeginPlay()
{
    Super::BeginPlay();
}

void ARisingLogSpawner::OnOverlapBegin(UPrimitiveComponent* /*OverlappedComp*/,
    AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/,
    int32 /*OtherBodyIndex*/,
    bool /*bFromSweep*/,
    const FHitResult& /*SweepResult*/)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap! Spawning..."));
    UE_LOG(LogTemp, Warning, TEXT("OverlapBegin: %s"), *OtherActor->GetName());
    // Only spawn when the player overlaps
    if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
    {
        OnSpawn(); // For blueprint purposes.
        FActorSpawnParameters Params;
        Params.Owner = this;
        GetWorld()->SpawnActor<ARisingLogActor>(PlatformClass, SpawnLocation, FRotator::ZeroRotator, Params);  // spawn actor :contentReference[oaicite:9]{index=9}
        Destroy();
    }
}
