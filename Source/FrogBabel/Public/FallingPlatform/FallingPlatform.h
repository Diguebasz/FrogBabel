// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingPlatform.generated.h"

UCLASS()
class FROGBABEL_API AFallingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingPlatform();

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggers")
	void OnFall();

	UFUNCTION(BlueprintImplementableEvent, Category = "Triggers")
	void OnContact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:
	// Flag to ensure we only trigger once
	bool bHasBeenTriggered;

	// Reference to the platform mesh
	UStaticMeshComponent* PlatformStaticMesh;

};
