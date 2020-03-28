// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LylatArwing.generated.h"

class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class USoundBase;
class UAnimMontage;

UCLASS(config=Game)
class ALylatArwing : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    USkeletalMeshComponent* ArwingMesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* Camera;

public:
    ALylatArwing();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BaseAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BoostAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BreakAcceleration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    UAnimMontage* LaserFireAnimation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* LaserFireSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int BoostMeterLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int LaserAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserDelayInSeconds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    FVector LaserOffset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserRange;

protected:
    void OnLaserFire();
    
    void OnMoveVertical(float value);
    void OnMoveHorizontal(float value);
    void OnTurn(float value);
    void OnLookUp(float value);

    FHitResult LaserTrace(const FVector& begin, const FVector& end) const;

    virtual void SetupPlayerInputComponent(class UInputComponent* component);

public:
    FORCEINLINE class USkeletalMeshComponent* GetArwingMesh() const { return ArwingMesh; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};