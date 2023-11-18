// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObject.generated.h"

UCLASS()
class MATHNANOPROJECT_API AMovingObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingObject();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	FVector Start;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
	FVector GoalPosition;

	float incrementing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
