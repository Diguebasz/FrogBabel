// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC_Base.h"

// Sets default values
ANPC_Base::ANPC_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AIBrain = CreateDefaultSubobject<UAIPerceptionComponent>("Happy Brain");

}

// Called when the game starts or when spawned
void ANPC_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC_Base::SensePlayer()
{
}



void ANPC_Base::GenerateNavigableNavPoints()
{
    FVector LocalActorLocation = GetActorLocation();  // Get the actor's position in world space
    
    // Access the navigation system
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    // Check to see if we find Nav
    if (!NavSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("Navigation System not found!"));
        return;
    }

    for (int32 i = 0; i < numberOfNavPoints; ++i)
    {
        FVector RandomDirection = UKismetMathLibrary::RandomUnitVector();  // Get a random direction
        FVector PotentialTargetLocation = LocalActorLocation + RandomDirection * FMath::RandRange(50.f, GenerationAreaRadius);  // Scale it to the radius
        FNavAgentProperties NPCProperties;
        NPCProperties.AgentHeight = 50.f; // Defining height of the NPC

    	// Check if the point is pathable using the navigation system
        FNavLocation NavPoint;
        if (NavSystem->ProjectPointToNavigation(PotentialTargetLocation, NavPoint, GenerationSphereRadius, &NPCProperties,nullptr))
        {
            // If the point is pathable, spawn a TargetPoint actor at that location

            if (ATargetPoint* PossibleLocation = GetWorld()->SpawnActor<ATargetPoint>(LocalActorLocation, FRotator::ZeroRotator))
            {
                PossibleLocation->SetActorLocation(NavPoint);  // Set the target location to the validated nav point
                PatrolPointsArray.Add(PossibleLocation);  // Store the target point in the array
            }
        }
        else
        {
            i--;  // Decrement the counter to try again
        }
    }
}


