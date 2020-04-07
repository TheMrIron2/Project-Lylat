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
    SpringArm->TargetArmLength = 600.f;
    SpringArm->SocketOffset = FVector(0.f, 70.f, 100.f);
    SpringArm->bEnableCameraLag = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    Particles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
    Particles->SetupAttachment(RootComponent);
    //Particles->Material

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

    currentAccel = BaseAcceleration;
}

void ALylatArwing::SetupPlayerInputComponent(class UInputComponent* component)
{
    check(component);

    component->BindAction("Fire", IE_Pressed, this, &ALylatArwing::OnLaserFire);

    component->BindAction("Boost", IE_Pressed, this, &ALylatArwing::OnBoost);
    component->BindAction("Boost", IE_Released, this, &ALylatArwing::OnBoostBreakRelease);

    component->BindAction("Break", IE_Pressed, this, &ALylatArwing::OnBreak);
    component->BindAction("Break", IE_Released, this, &ALylatArwing::OnBoostBreakRelease);

    component->BindAction("MoveUp", IE_Pressed, this, &ALylatArwing::OnMoveUp);
    component->BindAction("MoveDown", IE_Pressed, this, &ALylatArwing::OnMoveDown);
    component->BindAction("MoveLeft", IE_Pressed, this, &ALylatArwing::OnMoveLeft);
    component->BindAction("MoveRight", IE_Pressed, this, &ALylatArwing::OnMoveRight);
}

void ALylatArwing::Tick(float delta)
{
    Super::Tick(delta);

    SetActorLocation(FVector(GetActorLocation().X + currentAccel, GetActorLocation().Y, GetActorLocation().Z));
}

void ALylatArwing::NotifyHit(class UPrimitiveComponent* current, class AActor* other, class UPrimitiveComponent* otherComp, bool bSelfMoved, FVector hitLocation, FVector hitNormal, FVector normalImpulse, const FHitResult& hit)
{
    Super::NotifyHit(current, other, otherComp, bSelfMoved, hitLocation, hitNormal, normalImpulse, hit);
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
    currentAccel = BoostAcceleration;
    SpringArm->TargetArmLength = 800.f;
    if (BoostSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, BoostSound, GetActorLocation());
}

void ALylatArwing::OnBreak()
{
    currentAccel = BreakAcceleration;
    SpringArm->TargetArmLength = 400.f;
    if (BreakSound != NULL) UGameplayStatics::PlaySoundAtLocation(this, BreakSound, GetActorLocation());
}

void ALylatArwing::OnBoostBreakRelease()
{
    currentAccel = BaseAcceleration;
    SpringArm->TargetArmLength = 600.f;
}

// TODO: Tick() blocks this. This should be replaced by animations, perhaps?

void ALylatArwing::OnMoveUp()
{   
    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 3.f));
}

void ALylatArwing::OnMoveDown()
{
    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 3.f));
}

void ALylatArwing::OnMoveLeft()
{
    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - 3.f, GetActorLocation().Z));
}

void ALylatArwing::OnMoveRight()
{
    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + 3.f, GetActorLocation().Z));
}

FHitResult ALylatArwing::LaserTrace(const FVector& begin, const FVector& end) const
{
    FHitResult Hit(ForceInit);
    return Hit;
}