// Copyright (c) 2020 Project Lylat.

#include "LylatArwingController.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"

ALylatArwingController::ALylatArwingController()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> ArwingMesh;
		FConstructorStatics() : ArwingMesh(TEXT("/Game/Meshes/Arwing.uasset")) { }
	};

	static FConstructorStatics ConstructorStatics;

	ArwingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArwingMesh0"));
	ArwingMesh->SetStaticMesh(ConstructorStatics.ArwingMesh.Get());
	RootComponent = ArwingMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 160.0f;
	SpringArm->SocketOffset = FVector(0.f,0.f,60.f);
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 15.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;
}

void ALylatArwingController::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	AddActorLocalOffset(LocalMove, true);

	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	AddActorLocalRotation(DeltaRotation);

	Super::Tick(DeltaSeconds);
}

void ALylatArwingController::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}


void ALylatArwingController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Speed", this, &ALylatArwingController::SpeedInput);
	PlayerInputComponent->BindAxis("Vertical", this, &ALylatArwingController::VerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &ALylatArwingController::HorizontalInput);
}

void ALylatArwingController::SpeedInput(float Value)
{
	bool bHasInput = !FMath::IsNearlyEqual(Value, 0.f);
	float CurrentAcc = bHasInput ? (Value * Acceleration) : (-0.5f * Acceleration);
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void ALylatArwingController::VerticalInput(float Value)
{
	float TargetPitchSpeed = (Value * TurnSpeed * -1.f);
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ALylatArwingController::HorizontalInput(float Value)
{
	float TargetYawSpeed = (Value * TurnSpeed);
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
	const bool bIsTurning = FMath::Abs(Value) > 0.2f;
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}
