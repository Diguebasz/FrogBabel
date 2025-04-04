// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPlatform/FallingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

AFallingPlatform::AFallingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create and set up mesh component
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	// Initialize variables
	bHasBeenTriggered = false;
	PlatformStaticMesh = PlatformMesh;
}

// Called when the game starts or when spawned
void AFallingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// Bind hit event
	PlatformMesh->OnComponentHit.AddDynamic(this, &AFallingPlatform::OnHit);
}

void AFallingPlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// Do Once functionality
	if (bHasBeenTriggered) return;
	bHasBeenTriggered = true;

	OnContact();

	// Cast to Character (equivalent to Cast To Character node)
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		// Set up a timer for the delay (0.8 seconds)
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
			{
				// Disable collision (Set Collision Enabled node equivalent)
				//PlatformStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

				// Set visibility off (Set Visibility node equivalent)
				//PlatformStaticMesh->SetVisibility(false, true);

				OnFall();
			}, 0.8f, false); // 0.8 second delay, false means it won't repeat
	}
}


