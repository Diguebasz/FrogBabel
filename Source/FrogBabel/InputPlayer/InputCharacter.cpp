// Fill out your copyright notice in the Description page of Project Settings.


#include "Frogbabel/InputPlayer/InputCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AInputCharacter::AInputCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add input mapping context
	// We check if the Player Controller is valid
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get local player subsystem
		// We check if the Enhanced Input Player Subsystem is valid
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add input context
			// if it is valid, we add the Input Mapping Context
			Subsystem->AddMappingContext(InputMapping, 0);

		}
	}

	// We check the Enhanced Input Component
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// We call the input Test Action, and if it is triggered we call the function TestInput
		Input->BindAction(TestAction, ETriggerEvent::Completed, this, &AInputCharacter::TestInput);
	}
}

void AInputCharacter::TestInput()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Orange, "PRESSED INPUT ACTION");
}

