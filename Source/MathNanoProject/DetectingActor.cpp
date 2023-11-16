// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectingActor.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADetectingActor::ADetectingActor()
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

bool ADetectingActor::ShouldTickIfViewportsOnly() const
{
	return false;
}

// Called when the game starts or when spawned
void ADetectingActor::BeginPlay()
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

void ADetectingActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(StabAction, ETriggerEvent::Started, this, &ADetectingActor::Stab);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADetectingActor::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ADetectingActor::ResetTopSpeed);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADetectingActor::Jump);
	}
}

void ADetectingActor::Stab(const FInputActionValue& Value)
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

void ADetectingActor::Move(const FInputActionValue& Value)
{
	MovementVector = Value.Get<FVector2D>();

	AddActorLocalOffset(FVector(MovementVector.X, MovementVector.Y, 0) * CurrentSpeed * GetWorld()->DeltaTimeSeconds);
}

void ADetectingActor::Jump(const FInputActionValue& Value)
{
}

void ADetectingActor::SetSpeed(float DeltaTime)
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

void ADetectingActor::ResetTopSpeed()
{
	MovementVector = FVector2d::Zero();
}

// Called every frame
void ADetectingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);

	const auto TargetRotation = FRotator(0, GetControlRotation().Yaw, 0);
	SetActorRotation(UKismetMathLibrary::RInterpTo_Constant(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, RotatingSpeed));
}
