// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatLaserProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"

typedef struct _meshLoader
{
    ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
    _meshLoader(const TCHAR* path) : Mesh(path) { }
} meshLoader;

ALylatLaserProjectile::ALylatLaserProjectile() 
{
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	Projectile->BodyInstance.SetCollisionProfileName("Projectile");
	Projectile->SetStaticMesh(meshLoader(TEXT("/Game/Models/Laser/Meshes/Laser.Laser")).Mesh.Get());
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

	//InitialLifeSpan = 3.0f;
}

void ALylatLaserProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (OtherActor != NULL && OtherActor != this && OtherComp != NULL) OtherComp->DestroyComponent();
	//Destroy();
}

void ALylatLaserProjectile::Tick(float delta)
{
    Super::Tick(delta);
	//SetActorLocation(FVector(GetActorLocation().X + 1.f, GetActorLocation().Y, GetActorLocation().Z));
}