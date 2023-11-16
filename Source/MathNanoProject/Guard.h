// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Guard.generated.h"

UCLASS()
class MATHNANOPROJECT_API AGuard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGuard();

	UFUNCTION(BlueprintCallable)
	float FindAngle(const FVector SelfForward, const FVector TargetForward);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ConeAngle = 90;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DetectionDistance = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial* AlertMaterial;

	UPROPERTY(BlueprintReadOnly)
	bool SeesPlayer;
	
	UPROPERTY()
	AActor* Player;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
