// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatArwing.generated.h"

UCLASS(config=Game)
class LYLAT_API ALylatArwing : public APawn
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* CharacterMesh;

    UPROPERTY(VisibleDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleDefaultsOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* Camera;

    UPROPERTY(VisibleDefaultsOnly, Category = Particles, meta = (AllowPrivateAccess = "true"))
    class UParticleSystemComponent* Particles;

    UPROPERTY(VisibleDefaultsOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
    class USceneComponent* LaserOffset;

public:
    ALylatArwing();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controls)
    float BaseAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controls)
    float BoostAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controls)
    float BreakAcceleration;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controls)
    float VerticalLimit;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Controls)
    float HorizontalLimit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* BoostSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* BreakSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* LaserFireSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    UStaticMesh* LaserModel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int BoostMeterLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int LaserAmount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserDelayInSeconds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserRange;

private:
    // this is incredibly crude, but whatever, I'm sorry
    bool boost;
    bool _break;
    bool up;
    bool down;
    bool right;
    bool left;

protected:
    void OnLaserFire();
    
    void OnBoost();
    void OnBoostRelease();

    void OnBreak();
    void OnBreakRelease();

    void OnMoveUp();
    void OnMoveUpRelease();

    void OnMoveDown();
    void OnMoveDownRelease();

    void OnMoveLeft();
    void OnMoveLeftRelease();

    void OnMoveRight();
    void OnMoveRightRelease();

    void OnPause();

    virtual void SetupPlayerInputComponent(class UInputComponent* component) override;
    virtual void Tick(float delta) override;
    virtual void NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit) override;

public:
    FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
    FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh; }
    FORCEINLINE class USceneComponent* GetLaserOffset() const { return LaserOffset; }
};
