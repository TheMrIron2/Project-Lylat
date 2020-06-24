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
