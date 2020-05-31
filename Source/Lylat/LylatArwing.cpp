// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatArwing.h"
#include "LylatGameHUD.h"
#include "LylatResourceLoader.h"
#include "LylatLaserProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"

ALylatArwing::ALylatArwing()
{
    CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arwing"));
    CharacterMesh->SetSkeletalMesh(LylatGetResource<USkeletalMesh>(TEXT("/Game/Models/Arwing/Meshes/Arwing.Arwing")));
    RootComponent = CharacterMesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 800.f;
    SpringArm->SocketOffset = FVector(0.f, 70.f, 100.f);
    SpringArm->bEnableCameraLag = true;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    LaserOffset = CreateDefaultSubobject<USceneComponent>(TEXT("Laser Offset"));
	LaserOffset->SetupAttachment(CharacterMesh);
	LaserOffset->SetRelativeLocation(FVector(250.f, 0.f, 10.f));
	LaserOffset->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));	

    Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
    Particles->SetupAttachment(RootComponent);

    BaseAcceleration    = 25.f;
    BoostAcceleration   = 100.f;
    BreakAcceleration   = 5.f;

    Tilt = 25.f;

    BoostSound = LylatGetResource<USoundBase>(TEXT("/Game/Effects/Boost.Boost"));
    BreakSound = LylatGetResource<USoundBase>(TEXT("/Game/Effects/Break.Break"));
    LaserFireSound = LylatGetResource<USoundBase>(TEXT("/Game/Effects/LaserOnce.LaserOnce"));
    
    rotation = GetActorRotation();
}

void ALylatArwing::SetupPlayerInputComponent(class UInputComponent* component)
{
    Super::SetupPlayerInputComponent(component);

    check(component);

    component->BindAction("Fire", IE_Pressed, this, &ALylatArwing::OnLaserFire);

    component->BindAction("Boost", IE_Pressed, this, &ALylatArwing::OnBoost);
    component->BindAction("Boost", IE_Released, this, &ALylatArwing::OnBoostRelease);

    component->BindAction("Break", IE_Pressed, this, &ALylatArwing::OnBreak);
    component->BindAction("Break", IE_Released, this, &ALylatArwing::OnBreakRelease);

    component->BindAction("MoveUp", IE_Pressed, this, &ALylatArwing::OnMoveUp);
    component->BindAction("MoveUp", IE_Released, this, &ALylatArwing::OnMoveUpRelease);

    component->BindAction("MoveDown", IE_Pressed, this, &ALylatArwing::OnMoveDown);
    component->BindAction("MoveDown", IE_Released, this, &ALylatArwing::OnMoveDownRelease);

    component->BindAction("MoveLeft", IE_Pressed, this, &ALylatArwing::OnMoveLeft);
    component->BindAction("MoveLeft", IE_Released, this, &ALylatArwing::OnMoveLeftRelease);
    
    component->BindAction("MoveRight", IE_Pressed, this, &ALylatArwing::OnMoveRight);
    component->BindAction("MoveRight", IE_Released, this, &ALylatArwing::OnMoveRightRelease);

    component->BindAction("Pause", IE_Pressed, this, &ALylatArwing::OnPause);
}

void ALylatArwing::Tick(float delta)
{
    Super::Tick(delta);

    float x = 0, y = 0, z = 0;

    if (up) z = 10.f;
    else if (down) z = -10.f;

    if (left)
    {
        y = -15.f;
        if (!(rotation.Roll <= -Tilt)) rotation.Roll -= 3.f;
    }
    else if (right)
    {
        y = 15.f;
        if (!(rotation.Roll >= Tilt)) rotation.Roll += 3.f;
    }
    else
    {
        if (rotation.Roll > 0.f) rotation.Roll -= 3.f;
        else if (rotation.Roll < 0.f) rotation.Roll += 3.f;
    }

    if (boost)
    {
        x = BoostAcceleration;
        if (SpringArm->TargetArmLength != 1000.f) SpringArm->TargetArmLength += 5.f;
    }
    else if (_break)
    {
        x = BreakAcceleration;
        if (SpringArm->TargetArmLength != 600.f) SpringArm->TargetArmLength -= 5.f;
    }
    else
    {
        x = BaseAcceleration;
        if (SpringArm->TargetArmLength != 800.f && SpringArm->TargetArmLength < 800.f) SpringArm->TargetArmLength += 5.f;
        else if (SpringArm->TargetArmLength != 800.f && SpringArm->TargetArmLength > 800.f) SpringArm->TargetArmLength -= 5.f;
    }

    SetActorLocation(FVector(GetActorLocation().X + x, GetActorLocation().Y + y, GetActorLocation().Z + z));
    SetActorRotation(rotation);
}

void ALylatArwing::NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
    Super::NotifyHit(current, other, otherComp, bSelfMoved, hitLocation, hitNormal, normalImpulse, hit);

    FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), hitNormal.ToOrientationQuat(), 0.025f));
}

void ALylatArwing::OnLaserFire()
{
    const FRotator SpawnRotation = GetControlRotation();
	const FVector SpawnLocation = ((LaserOffset != nullptr) ? LaserOffset->GetComponentLocation() : GetActorLocation());

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<ALylatLaserProjectile>(ALylatLaserProjectile::StaticClass(), SpawnLocation, SpawnRotation, ActorSpawnParams);

    if (LaserFireSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, LaserFireSound, GetActorLocation());
}
    
void ALylatArwing::OnBoost()
{
    boost = true;
    if (BoostSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, BoostSound, GetActorLocation());
}

void ALylatArwing::OnBoostRelease() { boost = false; }

void ALylatArwing::OnBreak()
{
    if (boost == true) return;

    _break = true;
    if (BreakSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, BreakSound, GetActorLocation());
}

void ALylatArwing::OnBreakRelease() { _break = false; }

void ALylatArwing::OnMoveUp() { up = true; }
void ALylatArwing::OnMoveUpRelease() { up = false; }

void ALylatArwing::OnMoveDown() { down = true; }
void ALylatArwing::OnMoveDownRelease() { down = false; }

void ALylatArwing::OnMoveLeft() { left = true; }
void ALylatArwing::OnMoveLeftRelease() { left = false; }

void ALylatArwing::OnMoveRight() { right = true; }
void ALylatArwing::OnMoveRightRelease() { right = false; }

void ALylatArwing::OnPause()
{
    ALylatGameHUD* hud = GetWorld()->GetFirstPlayerController()->GetHUD<ALylatGameHUD>();

    GetWorld()->GetFirstPlayerController()->Pause();
    hud->ShowPause();   
}
