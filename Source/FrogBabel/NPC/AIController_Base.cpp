// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_Base.h"

#include "NPC_Base.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

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

void AAIController_Base::SetupSightSystem()
{
    TheLyingEyes = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("THE EYES THAT SEE"));
    if (TheLyingEyes)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
        TheLyingEyes->SightRadius = 500.f; // how far can NPC see
        TheLyingEyes->LoseSightRadius = TheLyingEyes->SightRadius + 50.f; // at what distance it loses track of the player
        TheLyingEyes->PeripheralVisionAngleDegrees = 180.f; // how wide is the NPC's field of vision
        TheLyingEyes->SetMaxAge(5.f); // how long does individual stimulus lives in the NPC's memory
        TheLyingEyes->AutoSuccessRangeFromLastSeenLocation = 520.f; // how far from last remembered location NPC has to be in order to still be seen
        TheLyingEyes->DetectionByAffiliation.bDetectEnemies = true; // can see enemies filtered though query system?
        TheLyingEyes->DetectionByAffiliation.bDetectFriendlies = true; // can see friendlies filtered though query system?
        TheLyingEyes->DetectionByAffiliation.bDetectNeutrals = true; // can see neutrals filtered though query system?

        GetPerceptionComponent()->SetDominantSense(*TheLyingEyes->GetSenseImplementation());
        GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AAIController_Base::OnTargetDetected);
        GetPerceptionComponent()->ConfigureSense(*TheLyingEyes);

    }
}

void AAIController_Base::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
    if (ANPC_Base* const ch = Cast<ANPC_Base>(Actor))
    {
        GetBlackboardComponent()->SetValueAsBool("ISeeYou", Stimulus.WasSuccessfullySensed());
    }
}
