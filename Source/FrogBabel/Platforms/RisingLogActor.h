// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
#include "RisingLogActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class FROGBABEL_API ARisingLogActor : public AActor
{
	GENERATED_BODY()

public:
	ARisingLogActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// The mesh that will rise
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;  // created via CreateDefaultSubobject :contentReference[oaicite:2]{index=2}

	// How far (in Unreal units) to rise above the spawn point
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RiseHeight = 5000.f;

	// Speed (units/sec) at which to rise
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RiseSpeed = 2000.f;

	// Internal state
	FVector InitialLocation;
	FVector TargetLocation;
	bool    bRising = false;
};

