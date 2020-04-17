// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatLaserProjectile.h"
#include "LylatResourceLoader.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

ALylatLaserProjectile::ALylatLaserProjectile() 
{
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	Projectile->BodyInstance.SetCollisionProfileName("Projectile");
	Projectile->SetStaticMesh(LylatGetResource<UStaticMesh>(TEXT("/Game/Models/Laser/Meshes/Laser.Laser")));
	Projectile->OnComponentHit.AddDynamic(this, &ALylatLaserProjectile::OnHit);
	Projectile->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Projectile->CanCharacterStepUpOn = ECB_No;

	RootComponent = Projectile;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = Projectile;
	ProjectileMovement->InitialSpeed = 300.f;
	ProjectileMovement->MaxSpeed = 300.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 3.0f;
}

void ALylatLaserProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	if (otherActor != NULL && otherActor != this && otherComp != NULL) otherComp->DestroyComponent();
	Destroy();
}