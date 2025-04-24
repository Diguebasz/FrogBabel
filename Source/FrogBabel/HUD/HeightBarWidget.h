// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeightBarWidget.generated.h"

class RisingWater;

UCLASS()
class FROGBABEL_API UHeightBarWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    // Bind these to your widget components in the UMG designer.
    UPROPERTY(meta = (BindWidget))
    class UImage* ProgressBar;

    UPROPERTY(meta = (BindWidget))
    class UImage* PlayerIcon;

    UPROPERTY(meta = (BindWidget))
    class UImage* WaterIcon;

    UPROPERTY(meta = (BindWidget))
    class UImage* WaterSprite;

    UPROPERTY(meta = (BindWidget))
    class UImage* PlayerSprite;

    // Set these values to match the Z range in your game.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    float MinZ = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progress")
    float MaxZ = 10000.0f;

    // References to the actors whose positions drive the icons.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progress")
    AActor* PlayerActor;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progress")
    AActor* WaterActor;

protected:
    // Called to update the icon positions based on actor positions.
    void UpdateIcons();
};
