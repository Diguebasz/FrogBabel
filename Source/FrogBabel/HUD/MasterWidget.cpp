// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogBabel/HUD/MasterWidget.h"
#include "PickupWidget.h"
#include "HeightBarWidget.h"

void UMasterWidget::NativeConstruct()
{
    // Always call the parent implementation first.
    Super::NativeConstruct();

    // At this point, ChildWidgetA and ChildWidgetB should be automatically assigned 
    // based on your widget blueprint hierarchy.

    if (ChildWidgetA)
    {
        ChildWidgetA = CreateWidget<UPickupWidget>(GetWorld());
        if (ChildWidgetA)
        {
            ChildWidgetA->AddToViewport();
        }

        // For example, if ChildWidgetA has a button or some clickable element,
        // you can bind an event handler here.
        // ChildWidgetA->OnClicked.AddDynamic(this, &UMyBaseWidget::OnChildWidgetAClicked);
    }

    if (ChildWidgetB)
    {
        // Similarly, initialize or bind events for ChildWidgetB if needed.
    }
}

/*
#include "FrogBabel/HUD/PickupHud.h"
#include "FrogBabel/HUD/PickupWidget.h"
#include "HeightBarHud.h"
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
}*/

