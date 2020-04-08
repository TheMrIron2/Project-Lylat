// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatArwing.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"

// TODO: Maybe use T for types? Maybe convert them to classes?

typedef struct _meshLoader
{
    ConstructorHelpers::FObjectFinderOptional<UStaticMesh> Mesh;
    _meshLoader(const TCHAR* path) : Mesh(path) { }
} meshLoader;

typedef struct _particleLoader
{
    ConstructorHelpers::FObjectFinderOptional<UParticleSystem> Particles;
    _particleLoader(const TCHAR* path) : Particles(path) { }
} particleLoader;

typedef struct _skeletalMeshLoader
{
    ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> Mesh;
    _skeletalMeshLoader(const TCHAR* path) : Mesh(path) { }
} skeletalMeshLoader;

typedef struct _soundLoader
{
    ConstructorHelpers::FObjectFinderOptional<USoundBase> Sound;
    _soundLoader(const TCHAR* path) : Sound(path) { }
} soundLoader;

ALylatArwing::ALylatArwing()
{
    CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arwing"));
    CharacterMesh->SetSkeletalMesh(skeletalMeshLoader(TEXT("/Game/Models/Arwing/Meshes/Arwing.Arwing")).Mesh.Get());
    RootComponent = CharacterMesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 800.f;
    SpringArm->SocketOffset = FVector(0.f, 70.f, 100.f);
    SpringArm->bEnableCameraLag = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
    Particles->SetupAttachment(RootComponent);

    LaserModel = meshLoader(TEXT("/Game/Models/Laser/Meshes/Laser.Laser")).Mesh.Get();

    BaseAcceleration    = 25.f;
    BoostAcceleration   = 100.f;
    BreakAcceleration   = 5.f;

    VerticalLimit       = 30.f;
    HorizontalLimit     = 30.f;

    LaserAmount         = 1;
    LaserDamage         = 5.f;
    LaserDelayInSeconds = 0.1f;
    LaserOffset         = FVector(0.f, 5.f,0.f);
    LaserRange          = 500.f;

    BoostSound = soundLoader(TEXT("/Game/Effects/Boost.Boost")).Sound.Get();
    BreakSound = soundLoader(TEXT("/Game/Effects/Break.Break")).Sound.Get();
    LaserFireSound = soundLoader(TEXT("/Game/Effects/LaserOnce.LaserOnce")).Sound.Get();
}

void ALylatArwing::SetupPlayerInputComponent(class UInputComponent* component)
{
    check(component);

    component->BindAction("Restart", IE_Pressed, this, &ALylatArwing::OnRestart);

    component->BindAction("Fire", IE_Pressed, this, &ALylatArwing::OnLaserFire);

    component->BindAction("Boost", IE_Pressed, this, &ALylatArwing::OnBoost);
    component->BindAction("Boost", IE_Released, this, &ALylatArwing::OnBoostRelease);

    component->BindAction("Break", IE_Pressed, this, &ALylatArwing::OnBreak);
    component->BindAction("Break", IE_Released, this, &ALylatArwing::OnBoostRelease);

    component->BindAction("MoveUp", IE_Pressed, this, &ALylatArwing::OnMoveUp);
    component->BindAction("MoveUp", IE_Released, this, &ALylatArwing::OnMoveUpRelease);

    component->BindAction("MoveDown", IE_Pressed, this, &ALylatArwing::OnMoveDown);
    component->BindAction("MoveDown", IE_Released, this, &ALylatArwing::OnMoveDownRelease);

    component->BindAction("MoveLeft", IE_Pressed, this, &ALylatArwing::OnMoveLeft);
    component->BindAction("MoveLeft", IE_Released, this, &ALylatArwing::OnMoveLeftRelease);
    
    component->BindAction("MoveRight", IE_Pressed, this, &ALylatArwing::OnMoveRight);
    component->BindAction("MoveRight", IE_Released, this, &ALylatArwing::OnMoveRightRelease);
}

void ALylatArwing::Tick(float delta)
{
    Super::Tick(delta);

    float x = 0, y = 0, z = 0;

    if (up) z = -6.f;
    else if (down) z = 6.f;

    if (left) y = -6.f;
    else if (right) y = 6.f;

    if (boost)
    {
        x = BoostAcceleration;
        if (SpringArm->TargetArmLength != 1000.f) SpringArm->TargetArmLength = SpringArm->TargetArmLength = SpringArm->TargetArmLength + 5;
    }
    else if (_break)
    {
        x = BreakAcceleration;
        if (SpringArm->TargetArmLength != 600.f) SpringArm->TargetArmLength = SpringArm->TargetArmLength = SpringArm->TargetArmLength - 5;
    }
    else
    {
        x = BaseAcceleration;
        if (SpringArm->TargetArmLength != 800.f && SpringArm->TargetArmLength < 800.f) SpringArm->TargetArmLength = SpringArm->TargetArmLength = SpringArm->TargetArmLength + 5;
        else if (SpringArm->TargetArmLength != 800.f && SpringArm->TargetArmLength > 800.f) SpringArm->TargetArmLength = SpringArm->TargetArmLength = SpringArm->TargetArmLength - 5;
    }

    SetActorLocation(FVector(GetActorLocation().X + x, GetActorLocation().Y + y, GetActorLocation().Z - z));
}

void ALylatArwing::NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
    Super::NotifyHit(current, other, otherComp, bSelfMoved, hitLocation, hitNormal, normalImpulse, hit);
}

void ALylatArwing::OnRestart()
{
    GetWorld()->ServerTravel(FString("/Game/Maps/Map1.Map1"), true, true);
}

void ALylatArwing::OnLaserFire()
{
    if (LaserFireSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, LaserFireSound, GetActorLocation());

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
        
    FVector ShootDir = FVector::ZeroVector;
    FVector StartTrace = FVector::ZeroVector;

    if (PlayerController)
    {
        FRotator CamRot;
        PlayerController->GetPlayerViewPoint(StartTrace, CamRot);
        ShootDir = CamRot.Vector();

        StartTrace = StartTrace + ShootDir * ((GetActorLocation() - StartTrace) | ShootDir);
    }

    const FVector EndTrace = StartTrace + ShootDir * LaserRange;
    const FHitResult Impact = LaserTrace(StartTrace, EndTrace);

    AActor* DamagedActor = Impact.GetActor();
    UPrimitiveComponent* DamagedComponent = Impact.GetComponent();

    if ((DamagedActor != NULL) && (DamagedActor != this) && (DamagedComponent != NULL) && DamagedComponent->IsSimulatingPhysics()) DamagedComponent->AddImpulseAtLocation(ShootDir * LaserDamage, Impact.Location);
}
    
void ALylatArwing::OnBoost()
{
    boost = true;
    if (BoostSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, BoostSound, GetActorLocation());
}

void ALylatArwing::OnBoostRelease() { boost = false; }

void ALylatArwing::OnBreak()
{
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

FHitResult ALylatArwing::LaserTrace(const FVector& begin, const FVector& end) const
{
    FHitResult Hit(ForceInit);
    return Hit;
}