// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObject.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMovingObject::AMovingObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->AttachToComponent(Root, FAttachmentTransformRules::KeepRelativeTransform);
	
}

// Called when the game starts or when spawned
void AMovingObject::BeginPlay()
{
	Super::BeginPlay();
	Start = UKismetMathLibrary::InverseTransformLocation(Mesh->GetComponentTransform() ,Mesh->GetComponentLocation());
	incrementing = FMath::RandRange(0, 100000);
}

// Called every frame
void AMovingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	incrementing += DeltaTime;
	float PerlinNoise = UKismetMathLibrary::PerlinNoise1D(incrementing);
	Mesh->SetRelativeLocation(FMath::Lerp(Start, GoalPosition, PerlinNoise), false);
}
