// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CPP_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class FROGBABEL_API UCPP_FindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Blueprintable, Category= "AIData", meta = (AllowPrivateAccess="true") )
	float NavigationRadius = 1500.f;

public:
	explicit UCPP_FindRandomLocation(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
