// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"

#include "NPC_Base.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AAIController_Base::AAIController_Base()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("BlackBoard Component");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
}

void AAIController_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    //if (!BlackboardComponent && !BehaviorTreeComponent) return;

    UseBlackboard(BlackboardDataPtr, BlackboardComponent);
    RunBehaviorTree(BehaviourTreePtr);

}