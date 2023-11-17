// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionSystem.h"

// Sets default values
ACollisionSystem::ACollisionSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


bool ACollisionSystem::AABBIntersect(const FVector MinA, const FVector MaxA, const FVector MinB, const FVector MaxB)
{
	if (MinA.X > MaxB.X || MinB.X > MaxA.X)
		return false;

	if (MinA.Y > MaxB.Y || MinB.Y > MaxA.Y)
		return false;

	if (MinA.Z > MaxB.Z || MinB.Z > MaxA.Z)
		return false;

	return true;
}

// Called every frame
void ACollisionSystem::Tick(float DeltaTime)
{
	if (AABBIntersect(CollissionBoxes[0]->GetActorLocation() + CollissionBoxes[0]->Min,
	                  CollissionBoxes[0]->GetActorLocation() + CollissionBoxes[0]->Max,
	                  CollissionBoxes[1]->GetActorLocation() + CollissionBoxes[1]->Min,
	                  CollissionBoxes[1]->GetActorLocation() + CollissionBoxes[1]->Max))
	{
		return;
	}
	for (auto box : CollissionBoxes)
	{
		box->ApplyGravity();
	}
}
