// Fill out your copyright notice in the Description page of Project Settings.


#include "FrogBabel/Water/RisingWater.h"

// Sets default values
ARisingWater::ARisingWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARisingWater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARisingWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

