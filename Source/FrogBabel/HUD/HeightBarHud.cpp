// Fill out your copyright notice in the Description page of Project Settings.

/*
#include "FrogBabel/HUD/HeightBarHud.h"

// MyHUD.cpp
#include "Engine/Canvas.h"
#include "GameFramework/Controller.h"
#include "FrogBabelCharacter.generated.h" // your character class

void AHeightBarHud::DrawHUD()
{
	Super::DrawHUD();

	// Define the bar's position and size on screen
	const float BarX = 50.0f;
	const float BarY = 50.0f;
	const float BarWidth = 20.0f;
	const float BarHeight = 200.0f;

	// Draw the background bar (gray)
	DrawRect(FLinearColor::Gray, BarX, BarY, BarWidth, BarHeight);

	// Get the player character
	APlayerController* PC = GetOwningPlayerController();
	if (PC)
	{
		TObjectPtr<AFrogBabelCharacter> MyChar = Cast<AFrogBabelCharacter>(PC->GetPawn());
		if (MyChar)
		{
			// Get the player's current Z position
			float PlayerZ = MyChar->GetActorLocation().Z;

			// Normalize the height (clamp between 0 and 1)
			float NormalizedHeight = FMath::Clamp((PlayerZ - MinZ) / (MaxZ - MinZ), 0.0f, 1.0f);

			// Calculate the Y position for the indicator.
			// (Assuming you want the indicator at the bottom for MinZ and at the top for MaxZ.)
			float IndicatorY = BarY + BarHeight - (NormalizedHeight * BarHeight);

			// Draw the indicator (green rectangle) – adjust size as needed
			const float IndicatorHeight = 10.0f;
			DrawRect(FLinearColor::Green, BarX, IndicatorY - IndicatorHeight * 0.5f, BarWidth, IndicatorHeight);
		}
	}
}
*/
/*
// MyHUD.cpp
#include "FrogBabel/HUD/HeightBarHud.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AHeightBarHud::DrawHUD()
{
	Super::DrawHUD();

	// Get the player pawn
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!PlayerPawn)
	{
		return;
	}

	// Get player's current Z position
	float PlayerZ = PlayerPawn->GetActorLocation().Z;

	// Clamp the player's Z position between MinHeight and MaxHeight
	float ClampedZ = FMath::Clamp(PlayerZ, MinHeight, MaxHeight);

	// Normalize the value (0.0f to 1.0f)
	float NormalizedHeight = (ClampedZ - MinHeight) / (MaxHeight - MinHeight);

	// Define the height bar dimensions and position
	const float BarWidth = 20.0f;
	const float BarHeight = 200.0f;
	const FVector2D BarPosition(50.0f, 50.0f); // Top left corner of the bar

	// Draw the bar background (a gray rectangle)
	DrawRect(FLinearColor::Gray, BarPosition.X, BarPosition.Y, BarWidth, BarHeight);

	// Calculate the marker's position on the bar
	// (1.0f - NormalizedHeight) because in screen space Y increases downward
	const float MarkerHeight = 10.0f; // Height of the marker
	float MarkerY = BarPosition.Y + (1.0f - NormalizedHeight) * BarHeight - (MarkerHeight * 0.5f);

	// Draw the marker (a green rectangle)
	DrawRect(FLinearColor::Green, BarPosition.X, MarkerY, BarWidth, MarkerHeight);
}*/

// In your HUD or game logic class:
/*if (HeightBarWidgetClass)
{
	UHeightBarWidget* HeightBarWidget = CreateWidget<UHeightBarWidget>(GetWorld(), HeightBarWidgetClass);
	if (HeightBarWidget)
	{
		HeightBarWidget->AddToViewport();
		// Store HeightBarWidget for later updates.
	}
}

// Later, update the thresholds (this could be in Tick or via events):
void UpdateHeightBarMarkers()
{
	// Example: Get actor heights.
	float Height1 = Actor1->GetActorLocation().Z;
	float Height2 = Actor2->GetActorLocation().Z;

	// Define the min and max height represented by your bar.
	const float MinHeight = 0.f;
	const float MaxHeight = 1000.f;  // adjust as needed

	// Normalize the heights.
	float Norm1 = (Height1 - MinHeight) / (MaxHeight - MinHeight);
	float Norm2 = (Height2 - MinHeight) / (MaxHeight - MinHeight);

	// Update the widget.
	if (HeightBarWidget)
	{
		HeightBarWidget->UpdateThresholdPositions(Norm1, Norm2);
	}
}*/
