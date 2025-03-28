// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PickupHud.generated.h"

class UPickupWidget;
/**
 *
 */
UCLASS()
class FROGBABEL_API APickupHud : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "YouTube Demo")
	TSubclassOf<UPickupWidget> CoinPickupWidgetClass;

	UPROPERTY()
	TObjectPtr<UPickupWidget> CoinPickupWidget;

public:
	virtual void BeginPlay() override;
};