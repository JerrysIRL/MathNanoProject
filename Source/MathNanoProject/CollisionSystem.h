// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionObject.h"
#include "IntersectionSystem.h"
#include "GameFramework/Actor.h"
#include "CollisionSystem.generated.h"

UCLASS()
class MATHNANOPROJECT_API ACollisionSystem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollisionSystem();

	UPROPERTY(EditAnywhere)
	TArray<ACollisionObject*> CollissionBoxes;

	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool AABBIntersect(const FVector MinA,
		const FVector MaxA,
		const FVector MinB,
		const FVector MaxB);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
