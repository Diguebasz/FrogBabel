// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Engine/TargetPoint.h"
#include "Perception/AIPerceptionTypes.h"
#include "NPC_Base.h"
#include "AIController_Base.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class FROGBABEL_API AAIController_Base : public AAIController
{
	GENERATED_BODY()

public:

	// Constructor
	explicit AAIController_Base();

protected:
	virtual void OnPossess(APawn* InPawn);

public:
	// Variables
	UPROPERTY(EditAnywhere, Category = "AIData")
	TObjectPtr<UBehaviorTree> BehaviourTreePtr;
	UPROPERTY(EditAnywhere, Category = "AIData")
	TObjectPtr<UBlackboardData> BlackboardDataPtr;


	// Component
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

private:
	class UAISenseConfig_Sight* TheLyingEyes;

	void SetupSightSystem();

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus);
};
