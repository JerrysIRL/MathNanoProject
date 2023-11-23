// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputMappingContext.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "DetectingPawn.generated.h"

UCLASS()
class MATHNANOPROJECT_API ADetectingPawn : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADetectingPawn();

	UPROPERTY(EditAnywhere)
	AActor* ActorToCheck;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input")
	UInputMappingContext* InputContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input")
	UInputAction* StabAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* NoseMesh;
	
	UPROPERTY(EditAnywhere)
	float DetectionLength = 100;

	UPROPERTY(EditAnywhere)
	float JumpForce = 100;

	UPROPERTY(EditAnywhere)
	float coneAngle = 90;

	UPROPERTY(EditAnywhere)
	float TopSpeed = 300;

	UPROPERTY(EditAnywhere)
	float StabbingDistance = 200;

	UPROPERTY(EditAnywhere)
	float RotatingSpeed = 150;

	UPROPERTY(EditAnywhere)
	float AccelerationTime = 3;

	FVector2D MovementVector;
	
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void Stab(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void SetSpeed(float DeltaTime);

	void ResetTopSpeed();

	float CurrentSpeed;

	float ElapsedTime = 0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
