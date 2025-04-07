// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/TargetPoint.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavFilters/NavigationQueryFilter.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "FrogBabel/Interfaces/CPP_StunnableInterface.h"
#include "Perception/AIPerceptionComponent.h"

#include "NPC_Base.generated.h"

class ATargetPoint;

UCLASS()
class FROGBABEL_API ANPC_Base : public ACharacter, public ICPP_StunnableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_Base();
	
	// Navigation Properties
	UPROPERTY(EditAnywhere, Category = "AIData")
	TArray<ATargetPoint*> PatrolPointsArray;
	UPROPERTY(EditAnywhere, Category = "RawData")
	FVector ActorLocation;

	// Helper Navigation Properties
	UPROPERTY(EditAnywhere, Category= "RawData")
	int32 numberOfNavPoints = 3;
	UPROPERTY(EditAnywhere, Category = "RawData")
	float GenerationAreaRadius = 50.f;
	UPROPERTY()
	FVector GenerationSphereRadius = FVector(GenerationAreaRadius, GenerationAreaRadius, GenerationAreaRadius);
	

	UPROPERTY(EditAnywhere = "AIData")
	UAIPerceptionComponent* AIBrain;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sense function for NPC to detect player
	void SensePlayer();

	// Should in theory generate desired amount of pathable points within defined radius
	void GenerateNavigableNavPoints();

};
