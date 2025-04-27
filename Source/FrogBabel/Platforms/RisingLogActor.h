// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
#include "RisingLogActor.generated.h"

class UStaticMeshComponent;
class ATreeActor;

UENUM()
enum class ELogState : uint8
{
	Rising,
	Rotating,
	Sinking
};

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
	//FVector InitialLocation;
	FVector TargetLocation;
	bool    bRising = false;


	// 1) Reference actor to define rotation axis
	UPROPERTY(EditAnywhere, Category = "Rotation")
	ATreeActor* RotationTarget;  // assign in Editor or via ConstructorHelpers :contentReference[oaicite:0]{index=0}

	// 2) How fast (deg/sec) to spin once at top
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float RotateSpeed = 90.f;  // degrees per second :contentReference[oaicite:1]{index=1}

	// 3) After rotating this many degrees, start sinking
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float TotalRotateAngle = 360.f;

	// 4) Descend speed (units/sec)
	UPROPERTY(EditAnywhere, Category = "Movement")
	float SinkSpeed = 200.f;

	// Internal state
	ELogState CurrentState = ELogState::Rising;
	float       AccumulatedRotation = 0.f;
	FVector     InitialLocation;
	FVector     TopLocation;
};