// Copyright 2020 Team Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatEnemy.generated.h"

UCLASS()
class LYLAT_API ALylatEnemy : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* CharacterMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* LaserOffset;

public:
	ALylatEnemy();

public:	
	virtual void Tick(float delta) override;
	virtual void NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit) override;

	FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh; }
    FORCEINLINE class USceneComponent* GetLaserOffset() const { return LaserOffset; }
};
