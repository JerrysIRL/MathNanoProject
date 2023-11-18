
#include "CollisionObject.h"


void ACollisionObject::ApplyGravity()
{
	auto NewLocation = GetActorLocation() + Gravity;
	if(GetActorLocation().Z + Min.Z < 0)
		return;
	SetActorLocation( NewLocation, false);
}
