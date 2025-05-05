// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "RisingLogActor.generated.h"

class UStaticMeshComponent;
class ATreeActor;

UENUM(BlueprintType)
enum class ERiseSinkState : uint8
{
    Rising     UMETA(DisplayName = "Rising"),
    Sinking    UMETA(DisplayName = "Sinking"),
    Finished   UMETA(DisplayName = "Finished")
};

UCLASS()
class FROGBABEL_API ARisingLogActor : public AActor
{
    GENERATED_BODY()

public:
    ARisingLogActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    /** The mesh to display */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* MeshComp;

    /** How far up (in Unreal units) to rise */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rise/Sink")
    float RiseHeight = 6000.f;

    /** How long (seconds) the rising phase lasts */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rise/Sink")
    float RiseDuration = 2.f;

    /** How long (seconds) the sinking phase lasts */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rise/Sink")
    float SinkDuration = 4.f;

    /** Set this after spawning so we know what to fall away from */
    UPROPERTY(BlueprintReadWrite, Category = "Fall Away")
    ATreeActor* TreeActor = nullptr;

private:
    /** Original world location when spawned */
    FVector OriginLocation;

    /** Tracks time within current phase */
    float ElapsedTime = 0.f;

    float LingerTime = 0.f;

    /** Current state */
    ERiseSinkState CurrentState = ERiseSinkState::Rising;

    /** Advance the rising logic */
    void HandleRising(float DeltaTime);

    /** Advance the sinking logic */
    void HandleSinking(float DeltaTime);
};