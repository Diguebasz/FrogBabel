// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_FindRandomLocation.h"
#include "AIController_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"



UCPP_FindRandomLocation::UCPP_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location Around Self";
}

EBTNodeResult::Type UCPP_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AAIController_Base* const cont = Cast<AAIController_Base>(OwnerComp.GetAIOwner()))
	{
		if (APawn* const npc = cont->GetPawn())
		{
			FVector const Origin = npc->GetActorLocation();

			if (UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				if (NavSys->GetRandomPointInNavigableRadius(Origin, NavigationRadius, Loc))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
