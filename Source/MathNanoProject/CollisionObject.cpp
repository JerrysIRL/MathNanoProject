
#include "CollisionObject.h"

void ACollisionObject::BeginPlay()
{
	Super::BeginPlay();
}

void ACollisionObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACollisionObject::ApplyGravity()
{
	auto NewLocation = GetActorLocation() + Gravity;
	if(GetActorLocation().Z + Min.Z < 0)
		return;
	SetActorLocation( NewLocation, false);
}
