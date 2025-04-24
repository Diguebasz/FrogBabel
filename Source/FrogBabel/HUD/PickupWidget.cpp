// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogBabel/HUD/PickupWidget.h"

#include "Components/TextBlock.h"
#include "FrogBabel/Pickup/PickupActor.h"

#include "Kismet/GameplayStatics.h"

void UPickupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CoinActorClass, FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (!Actor) continue;
		if (APickupActor* Coin = Cast<APickupActor>(Actor))
		{
			Coin->OnCoinPickup.AddDynamic(this, &UPickupWidget::OnCoinPickup);
		}
	}
}

void UPickupWidget::OnCoinPickup()
{
	CoinCount++;
	PickupCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CoinCount)));
}