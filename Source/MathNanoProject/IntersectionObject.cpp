// Fill out your copyright notice in the Description page of Project Settings.


#include "IntersectionObject.h"

// Sets default values
AIntersectionObject::AIntersectionObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntersectionObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIntersectionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawMyBox();
}

//Martins drawDebug box function, handy
void AIntersectionObject::DrawMyBox()
{
	const auto A = FVector(Min.X, Min.Y, Max.Z);
	const auto B = FVector(Max.X, Max.Y, Min.Z);
	const auto C = FVector(Min.X, Max.Y, Min.Z);
	const auto D = FVector(Max.X, Min.Y, Max.Z);
	const auto E = FVector(Max.X, Min.Y, Min.Z);
	const auto F = FVector(Min.X, Max.Y, Max.Z);
		
	DrawDebugPoint(
		GetWorld(),
		GetActorLocation() + Min,
		25.f,
		BoxColor
		);

	DrawDebugPoint(
		GetWorld(),
		GetActorLocation() + Max,
		25.f,
		BoxColor
		);
		
	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Max,
		GetActorLocation() + B,
		BoxColor
		);
		
	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Min,
		GetActorLocation() + A,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Min,
		GetActorLocation() + C,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + C,
		GetActorLocation() + F,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + C,
		GetActorLocation() + B,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Max,
		GetActorLocation() + F,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Max,
		GetActorLocation() + D,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + D,
		GetActorLocation() + A,
		BoxColor
		);
		
	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + A,
		GetActorLocation() + F,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + D,
		GetActorLocation() + E,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + B,
		GetActorLocation() + E,
		BoxColor
		);

	DrawDebugLine(
		GetWorld(),
		GetActorLocation() + Min,
		GetActorLocation() + E,
		BoxColor
		);	
}
