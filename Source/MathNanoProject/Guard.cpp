// Fill out your copyright notice in the Description page of Project Settings.


#include "Guard.h"
#include "Kismet/GameplayStatics.h"


AGuard::AGuard()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AGuard::BeginPlay()
{
	Super::BeginPlay();
	const auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Player = Controller->GetPawn();
}


void AGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugCone(GetWorld(), GetActorLocation(), GetActorForwardVector(), DetectionDistance, FMath::DegreesToRadians(ConeAngle * 0.5), 0, 1, FColor::Red);

	auto PlayerLocalPosition = GetActorTransform().InverseTransformPosition(Player->GetActorLocation());
	const auto Direction = (Player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	const float Angle = FindAngle(GetActorForwardVector(), Direction);
	const float Distance = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	//UE_LOG(LogTemp, Warning, TEXT("Angle to Player is : %f"), Angle);

	if (PlayerLocalPosition.X > 0
		&& Angle < ConeAngle * 0.5
		&& Distance <= DetectionDistance)
	{
		SeesPlayer = true;
		UE_LOG(LogTemp, Warning, TEXT("I see you, GET BACK HERE!"));
	}	
	else
	{
		SeesPlayer = false;
	}
}


float AGuard::FindAngle(const FVector SelfForward, const FVector TargetForward)
{
	auto Dot = FVector::DotProduct(SelfForward, TargetForward);
	Dot = FMath::Clamp(Dot, -1.f, 1.f);
	return FMath::RadiansToDegrees(FMath::Acos(Dot));
}
