// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IntersectionObject.h"
#include "GameFramework/Actor.h"
#include "IntersectionSystem.generated.h"

UCLASS()
class MATHNANOPROJECT_API AIntersectionSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionSystem();

	UPROPERTY(EditAnywhere)
	TArray<AIntersectionObject*> IntersectionBoxes;


	AIntersectionObject* IntersectionBoxOne;
	AIntersectionObject* IntersectionBoxTwo;
	
	UFUNCTION(BlueprintCallable, Category = "Intersection")
	static bool AABBIntersect(const FVector MinA,
		const FVector MaxA,
		const FVector MinB,
		const FVector MaxB);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
