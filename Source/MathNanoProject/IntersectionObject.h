// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IntersectionObject.generated.h"

UCLASS()
class MATHNANOPROJECT_API AIntersectionObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIntersectionObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(MakeEditWidget = true))
	FVector Min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =(MakeEditWidget = true))
	FVector Max;

	FColor BoxColor;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DrawMyBox();
	

};
