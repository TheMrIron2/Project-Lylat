// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by any commercial entity.
//
// Under the category "content used without permission" falls any content regarding the "Star Fox" trademark.
// Star Fox is a registered trademark of Nintendo Co., Ltd.
// 
// Under the category "content used according to licensing" fall the Discord Game SDK and the Ultralight SDK.
// Discord is a registered trademark of Discord, Inc.
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

#include "Components/SkeletalMeshComponent.h"

ALylatEnemy::ALylatEnemy()
{
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy"));
    CharacterMesh->SetSkeletalMesh(LylatGetResource<USkeletalMesh>(TEXT("/Game/Models/Arwing/Meshes/Arwing.Arwing")));

	CharacterMesh->SetCollisionProfileName(TEXT("Enemy"));
	CharacterMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	CharacterMesh->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	CharacterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
	CharacterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CharacterMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

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
