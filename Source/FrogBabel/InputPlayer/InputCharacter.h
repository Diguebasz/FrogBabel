// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class FROGBABEL_API AInputCharacter : public ACharacter
{
	GENERATED_BODY()

	// Create Follow camera
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	// We create a reference to InputMapping
	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	class UInputMappingContext* InputMapping;

	// Here we create references to the different actions (I'm pretty sure)
	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category= "EnhancedInput")
	class UInputAction* LookAction;

public:
	// Sets default values for this character's properties
	AInputCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();

private:
	UPROPERTY(EditAnywhere, Category= "Fool's Foolish Look")
	class UAIPerceptionStimuliSourceComponent* SourceOfStimulus;

	void BecomeSensable();

};
