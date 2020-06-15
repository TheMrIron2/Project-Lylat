// Copyright 2020 Team Project Lylat. All Rights Reserved.

#include "LylatEnemy.h"
#include "LylatResourceLoader.h"

#include "Components/StaticMeshComponent.h"

ALylatEnemy::ALylatEnemy()
{
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy"));
    CharacterMesh->SetStaticMesh(LylatGetResource<UStaticMesh>(TEXT("/Game/Models/Arwing/Meshes/ArwingStaticMesh.ArwingStaticMesh")));

	CharacterMesh->SetCollisionProfileName(TEXT("Arwing"));
	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
    CharacterMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CharacterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	CharacterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

    RootComponent = CharacterMesh;

	LaserOffset = CreateDefaultSubobject<USceneComponent>(TEXT("Laser Offset"));
	LaserOffset->SetupAttachment(CharacterMesh);
	LaserOffset->SetRelativeLocation(FVector(250.f, 0.f, 10.f));
	LaserOffset->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));	

	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(true);
}

void ALylatEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALylatEnemy::NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
	Destroy();
}
