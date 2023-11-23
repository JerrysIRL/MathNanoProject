// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectingPawn.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADetectingPawn::ADetectingPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	NoseMesh = CreateDefaultSubobject<UStaticMeshComponent>("NoseMesh");
	NoseMesh->SetupAttachment(Mesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArm->SetupAttachment(Mesh);
	CameraComponent->SetupAttachment(SpringArm);
}

bool ADetectingPawn::ShouldTickIfViewportsOnly() const
{
	return false;
}

// Called when the game starts or when spawned
void ADetectingPawn::BeginPlay()
{
	Super::BeginPlay();
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (auto System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			System->AddMappingContext(InputContext, 0);
		}
	}
}

void ADetectingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(StabAction, ETriggerEvent::Started, this, &ADetectingPawn::Stab);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADetectingPawn::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ADetectingPawn::ResetTopSpeed);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ADetectingPawn::Jump);
	}
}

void ADetectingPawn::Stab(const FInputActionValue& Value)
{
	if (ActorToCheck)
	{
		float Dot = FVector::DotProduct(ActorToCheck->GetActorForwardVector(), GetActorForwardVector());
		Dot = FMath::Clamp(Dot, -1, 1);
		float Degrees = FMath::RadiansToDegrees(FMath::Acos(Dot));
		UE_LOG(LogTemp, Warning, TEXT("degrees : %f"), Degrees);

		const float Distance = FVector::Dist(GetActorLocation(), ActorToCheck->GetActorLocation());
		if (Degrees <= 40 && Distance <= StabbingDistance)
		{
			ActorToCheck->Destroy();
			ActorToCheck = nullptr; 
		}
	}
}

void ADetectingPawn::Move(const FInputActionValue& Value)
{
	MovementVector = Value.Get<FVector2D>();

	AddActorLocalOffset(FVector(MovementVector.X, MovementVector.Y, 0) * CurrentSpeed * GetWorld()->DeltaTimeSeconds);
}

void ADetectingPawn::Jump(const FInputActionValue& Value)
{
	Mesh->AddImpulse(FVector(0,0,JumpForce), NAME_None, true);
}

void ADetectingPawn::SetSpeed(float DeltaTime)
{
	if (MovementVector.Length() > 0.1)
	{
		ElapsedTime += DeltaTime / AccelerationTime;
		ElapsedTime = FMath::Clamp(ElapsedTime, 0, 1);
		CurrentSpeed = FMath::Lerp(0, TopSpeed, ElapsedTime);
	}
	else
	{
		ElapsedTime = 0;
	}
	UE_LOG(LogTemp, Warning, TEXT("CurrentSpeed: %f"), CurrentSpeed);
}

void ADetectingPawn::ResetTopSpeed()
{
	MovementVector = FVector2d::Zero();
}

// Called every frame
void ADetectingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);

	const auto TargetRotation = FRotator(0, GetControlRotation().Yaw, 0);
	SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, RotatingSpeed));
}
