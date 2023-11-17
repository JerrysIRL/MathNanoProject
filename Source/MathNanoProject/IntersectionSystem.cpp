// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionSystem.h"

// Sets default values
AIntersectionSystem::AIntersectionSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AIntersectionSystem::BeginPlay()
{
	Super::BeginPlay();

	IntersectionBoxOne = IntersectionBoxes[0];
	IntersectionBoxTwo = IntersectionBoxes[1];
}

// Called every frame
void AIntersectionSystem::Tick(float DeltaTime)
{
	if (AABBIntersect(IntersectionBoxOne->GetActorLocation() + IntersectionBoxOne->Min,
		IntersectionBoxOne->GetActorLocation() + IntersectionBoxOne->Max,
		IntersectionBoxTwo->GetActorLocation() + IntersectionBoxTwo->Min,
		IntersectionBoxTwo->GetActorLocation() + IntersectionBoxTwo->Max))
	{
		for (auto box : IntersectionBoxes)
		{
			box->BoxColor = FColor::Red;
		}
	}
	else
	{
		for (auto box : IntersectionBoxes)
		{
			box->BoxColor = FColor::Green;
		}
	}
}

bool AIntersectionSystem::AABBIntersect(const FVector MinA, const FVector MaxA, const FVector MinB, const FVector MaxB)
{
	if (MinA.X > MaxB.X || MinB.X > MaxA.X)
		return false;

	if (MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
		return false;

	if (MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
		return false;

	return true;
}
