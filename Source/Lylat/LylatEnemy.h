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
