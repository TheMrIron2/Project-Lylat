// Copyright 2020 Team Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatArwing.generated.h"

UCLASS()
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
    float Tilt;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* BoostSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* BreakSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    USoundBase* LaserFireSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Content)
    UStaticMesh* LaserModel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float LaserFireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    int BoostMeterLevel;

private:
    FRotator rotation;
    FTimerHandle timer;

    bool boost;
    bool _break;
    bool up;
    bool down;
    bool right;
    bool left;
    bool canShoot = true;

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

    void OnTimerDone();

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* component) override;
    virtual void Tick(float delta) override;

    FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
    FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
    FORCEINLINE class USkeletalMeshComponent* GetCharacterMesh() const { return CharacterMesh; }
    FORCEINLINE class USceneComponent* GetLaserOffset() const { return LaserOffset; }
};
