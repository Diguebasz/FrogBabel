// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MasterWidget.generated.h"

/**
 * 
 */
UCLASS()
class FROGBABEL_API UMasterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // These variables are automatically bound to the child widgets in your blueprint,
    // as long as the widget names match.
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UPickupWidget* ChildWidgetA;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    class UHeightBarWidget* ChildWidgetB;

protected:
    virtual void NativeConstruct() override;

};

/**
 *
 
UCLASS()
class FROGBABEL_API APickupHud : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPickupWidget> CoinPickupWidgetClass;

	UPROPERTY()
	TObjectPtr<UPickupWidget> CoinPickupWidget;

public:
	virtual void BeginPlay() override;
};*/
