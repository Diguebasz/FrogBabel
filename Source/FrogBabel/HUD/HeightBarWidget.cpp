// Fill out your copyright notice in the Description page of Project Settings.

#include "HeightBarWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "FrogBabel/Water/RisingWater.h"
#include "Math/UnrealMathUtility.h"

void UHeightBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Automatically attaching the player actor.
    PlayerActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARisingWater::StaticClass(), FoundActors);
    if (FoundActors.Num() > 0)
    {
        WaterActor = FoundActors[0];
    }
    else
    {
        WaterActor = nullptr;
        UE_LOG(LogTemp, Warning, TEXT("WaterActor is not present in-game!"));
    }
}

void UHeightBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    UpdateIcons();
}

void UHeightBarWidget::UpdateIcons()
{
    if (!PlayerActor || !WaterActor || !ProgressBar)
    {
        return;
    }

    // Get current Z positions.
    float PlayerZ = PlayerActor->GetActorLocation().Z;
    float WaterZ = WaterActor->GetActorLocation().Z;

    // Normalize these values (assumes MinZ at bottom and MaxZ at top).
    auto NormalizeZ = [this](float Z) -> float
        {
            return FMath::Clamp((Z - MinZ) / (MaxZ - MinZ), 0.0f, 1.0f);
        };

    float PlayerPercent = NormalizeZ(PlayerZ);
    float WaterPercent = NormalizeZ(WaterZ);

    // Get the size of the progress bar image.
    FVector2D BarSize = ProgressBar->GetCachedGeometry().GetLocalSize();

    // Calculate the new Y positions.
    // (Assuming that 0 corresponds to the bottom of the bar and 1 corresponds to the top.)
    float PlayerY = (1.0f - PlayerPercent) * BarSize.Y;

    // Update the PlayerIcon position.
    if (UCanvasPanelSlot* PlayerSlot = Cast<UCanvasPanelSlot>(PlayerIcon->Slot))
    {
        FVector2D CurrentPos = PlayerSlot->GetPosition();
        // Keep the current X position and update Y.
        PlayerSlot->SetPosition(FVector2D(CurrentPos.X, PlayerY));
    }
    
    float ScaleMultiplier = 1.0f; // Incase the water bar should rise faster or slower.
    float NewScaleY = FMath::Clamp(WaterPercent * ScaleMultiplier, 0.0f, 1.0f);

    FWidgetTransform CurrentTransform = WaterIcon->RenderTransform;
    CurrentTransform.Scale.Y = NewScaleY;
    WaterIcon->SetRenderTransform(CurrentTransform);
}
