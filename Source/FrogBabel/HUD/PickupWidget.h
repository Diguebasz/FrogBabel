// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupWidget.generated.h"

class APickupActor;
class UTextBlock;
/**
 *
 */
UCLASS()
class FROGBABEL_API UPickupWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "YouTube Demo", meta = (BindWidget))
	TObjectPtr<UTextBlock> PickupCountText;

	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	TSubclassOf<APickupActor> CoinActorClass;

	int CoinCount;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnCoinPickup();
};