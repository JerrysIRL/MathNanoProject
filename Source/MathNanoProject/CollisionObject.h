// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionObject.h"
#include "CollisionObject.generated.h"

/**
 * 
 */
UCLASS()
class MATHNANOPROJECT_API ACollisionObject : public AIntersectionObject
{
	GENERATED_BODY()
	

	UPROPERTY(EditAnywhere)
	FVector Gravity;

public:
	void ApplyGravity();
};
	