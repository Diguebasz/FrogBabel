// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupHud.h"

#include "FrogBabel/HUD/PickupWidget.h"
//#include "FrogBabel/HUD/HeightBarWidget.h"

void APickupHud::BeginPlay()
{
	Super::BeginPlay();

	if (CoinPickupWidgetClass)
	{
		CoinPickupWidget = CreateWidget<UPickupWidget>(GetWorld(), CoinPickupWidgetClass);
		if (CoinPickupWidget)
		{
			CoinPickupWidget->AddToViewport();
		}
	}
}