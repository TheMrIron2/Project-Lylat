// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by Nintendo or any other commercial entity.
// Under this category fall the Arwing and the Wolfen model along with their respective assets, as well as the Star Fox trademark.
// Any commercial content has been used without permission.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "LylatLaserProjectile.h"
#include "LylatResourceLoader.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ALylatLaserProjectile::ALylatLaserProjectile() 
{
	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	
	Projectile->BodyInstance.SetCollisionProfileName("Projectile");
	Projectile->SetStaticMesh(LylatGetResource<UStaticMesh>(TEXT("/Game/Models/Laser/Meshes/Laser.Laser")));

	Projectile->OnComponentHit.AddDynamic(this, &ALylatLaserProjectile::OnHit);
	Projectile->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Projectile->CanCharacterStepUpOn = ECB_No;

	RootComponent = Projectile;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = false;
	PrimaryActorTick.TickGroup = TG_DuringPhysics;

	InitialLifeSpan = 3.f;
	SetActorEnableCollision(true);
}

void ALylatLaserProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	if (otherActor != NULL && otherActor != this && otherComp != NULL) otherComp->DestroyComponent();
	Destroy();
}

void ALylatLaserProjectile::Tick(float delta)
{
	FVector position = GetActorLocation();
	position.X += 250.f;

	SetActorLocation(position);
}
