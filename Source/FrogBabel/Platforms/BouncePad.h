// Fill out your copyright notice in the Description page of Project Settings.
/*
UCLASS()
class FROGBABEL_API ABouncePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABouncePad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BouncePad.generated.h"

UCLASS()
class FROGBABEL_API ABouncePad : public AActor
{
    GENERATED_BODY()

public:
    ABouncePad();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class USceneComponent* DefaultSceneRoot;

    // Collision component used as the hitbox.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UBoxComponent* OverlapBox;

    // Mesh component for visualization (optional).
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UStaticMeshComponent* Mesh;

    // Arrow component to control launch direction and intensity.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    class UArrowComponent* LaunchDirection;

    // Launch strength multiplier.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BouncePad")
    float LaunchStrength;

    // Function called when something overlaps the hitbox.
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
