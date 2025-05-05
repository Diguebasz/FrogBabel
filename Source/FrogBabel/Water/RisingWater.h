// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RisingWater.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

/*UCLASS()
class FROGBABEL_API ARisingWater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARisingWater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};*/

/** Please add a class description */
UCLASS(Blueprintable, BlueprintType)
class FROGBABEL_API ARisingWater : public AActor
{
	GENERATED_BODY()
public:
	//Please add a variable description
	/*UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Box;

	// Please add a variable description
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Plane1;

	// Please add a variable description
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Plane;*/

	// Please add a variable description
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default", meta = (AllowPrivateAccess = "true"))
	double RiseSpeed;

	// Please add a variable description
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default", meta = (AllowPrivateAccess = "true"))
	double lifetime;

	// Sets default values for this actor's properties
	ARisingWater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
