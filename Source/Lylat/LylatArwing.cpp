// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatArwing.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ALylatArwing::ALylatArwing()
{
	struct meshConstruct
	{
		ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> CharacterMesh;
		meshConstruct() : CharacterMesh(TEXT("/Game/Models/Arwing/Meshes/Arwing.Arwing")) { }
	};

	static meshConstruct meshStatics;

	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arwing"));
	CharacterMesh->SetSkeletalMesh(meshStatics.CharacterMesh.Get());
	RootComponent = CharacterMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.f;
	SpringArm->SocketOffset = FVector(0.f, 70.f, 100.f);
	SpringArm->bEnableCameraLag = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

	BaseAcceleration 	= 10.f;
    BoostAcceleration 	= 100.f;
    BreakAcceleration 	= 5.f;

	LaserAmount			= 1;
	LaserDamage			= 5.f;
	LaserDelayInSeconds = 0.1f;
	LaserOffset 		= FVector(0.f, 5.f,0.f);
	LaserRange			= 500.f;

	struct soundConstruct
	{
		ConstructorHelpers::FObjectFinderOptional<USoundBase> LaserFireSound;
		soundConstruct() : LaserFireSound(TEXT("/Game/Effects/LaserOnce.LaserOnce")) { }
	};

	struct soundConstruct soundStatics;
	LaserFireSound = soundStatics.LaserFireSound.Get();

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
}

void ALylatArwing::OnBreak()
{
	currentAccel = BreakAcceleration;
}

void ALylatArwing::OnBoostBreakRelease()
{
	currentAccel = BaseAcceleration;
}

FHitResult ALylatArwing::LaserTrace(const FVector& begin, const FVector& end) const
{
    FHitResult Hit(ForceInit);
    return Hit;
}