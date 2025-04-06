// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MasterHud.generated.h"

class UPickupWidget;
class UHeightBarWidget;
//class AFrogBabelCharacter;
//class AWater;

/**
 * 
 */
UCLASS()
class FROGBABEL_API AMasterHud : public AHUD
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UPickupWidget> CoinPickupWidgetClass;

    UPROPERTY()
    TObjectPtr<UPickupWidget> CoinPickupWidget;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UHeightBarWidget> HudHeightBarWidgetClass;

    UPROPERTY()
    TObjectPtr<UHeightBarWidget> HudHeightBarWidget;

    /*UPROPERTY(EditDefaultsOnly)
    AFrogBabelCharacter* HudHudHeightBarWidgetClass;*/

    /*UPROPERTY(EditDefaultsOnly)
    AWater* HudHudHeightBarWidgetClass;*/

    /*
    // Array of widget classes you want to attach (assignable in editor)
    UPROPERTY(EditAnywhere, Category = "UI")
    TArray<TSubclassOf<class UUserWidget>> WidgetClasses;

    // Array of widget instances created at runtime
    UPROPERTY()
    TArray<UUserWidget*> WidgetInstances;*/
};
