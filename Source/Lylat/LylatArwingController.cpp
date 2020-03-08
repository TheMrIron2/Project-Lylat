// Copyright 2020 Project Lylat.

#include "LylatArwingController.h"

ALylatArwingController::ALylatArwingController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALylatArwingController::BeginPlay()
{
	Super::BeginPlay();
}

void ALylatArwingController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALylatArwingController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}