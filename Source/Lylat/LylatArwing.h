// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatArwing.generated.h"

UCLASS(config=Game)
class ALylatArwing : public APawn
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* CharacterMesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;

public:
    ALylatArwing();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BaseAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BoostAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Controls)
    float BreakAcceleration;

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

private:
    float currentAccel;

protected:
    void OnLaserFire();
    void OnBoost();
    void OnBreak();
    void OnBoostBreakRelease();

    FHitResult LaserTrace(const FVector& begin, const FVector& end) const;

    virtual void SetupPlayerInputComponent(class UInputComponent* component) override;
    virtual void Tick(float delta) override;
    virtual void NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit) override;

public:
    FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
    FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh; }
};