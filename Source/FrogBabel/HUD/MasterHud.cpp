// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogBabel/HUD/MasterHud.h"

//#include "Blueprint/UserWidget.h"
#include "FrogBabel/HUD/PickupWidget.h"
#include "FrogBabel/HUD/HeightBarWidget.h"
//#include "FrogBabelCharacter.h"
#include <Kismet/GameplayStatics.h>

void AMasterHud::BeginPlay()
{
    Super::BeginPlay();
    /*
    // Assuming this is called in a context where GetWorld() is valid (e.g. in BeginPlay)
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AFrogBabelCharacter* MyPlayer = Cast<AFrogBabelCharacter>(PlayerPawn);*/


    // Loop through each widget class and create an instance
    /*for (TSubclassOf<UUserWidget> WidgetClass : WidgetClasses)
    {*/
        if (CoinPickupWidgetClass)
        {
            CoinPickupWidget = CreateWidget<UPickupWidget>(GetWorld(), CoinPickupWidgetClass);
            if (CoinPickupWidget)
            {
                CoinPickupWidget->AddToViewport();
            }
        }
        // In your HUD or game logic class:
        if (HudHeightBarWidgetClass)
        {
            HudHeightBarWidget = CreateWidget<UHeightBarWidget>(GetWorld(), HudHeightBarWidgetClass);
            if (HudHeightBarWidget)
            {
                HudHeightBarWidget->AddToViewport();
                // Store HeightBarWidget for later updates.
            }
        }

        // Later, update the thresholds (this could be in Tick or via events):
        /*void UpdateHeightBarMarkers();
        {
            // Example: Get actor heights.
            //float Height1 = FrogBabelCharacter->GetActorLocation().Z;
            //float Height2 = Actor2->GetActorLocation().Z;

            // Define the min and max height represented by your bar.
            const float MinHeight = 0.f;
            const float MaxHeight = 1000.f;  // adjust as needed

            // Normalize the heights.
            //float Norm1 = (Height1 - MinHeight) / (MaxHeight - MinHeight);
            //float Norm2 = (Height2 - MinHeight) / (MaxHeight - MinHeight);

            // Update the widget.
            if (HudHeightBarWidget)
            {
                //HudHeightBarWidget->UpdateThresholdPositions(Norm1, Norm2);
            }
        }*/

    }
//}