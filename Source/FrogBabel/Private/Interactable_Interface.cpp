// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Interface.h"

// Sets default values
AInteractable_Interface::AInteractable_Interface()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractable_Interface::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable_Interface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

