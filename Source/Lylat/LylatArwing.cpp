// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatArwing.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

#define COLLISION_WEAPON		ECC_GameTraceChannel1

ALylatArwing::ALylatArwing()
{

}

void ALylatArwing::SetupPlayerInputComponent(class UInputComponent* component)
{
    
}

void ALylatArwing::OnLaserFire()
{

}
    
void ALylatArwing::OnMoveVertical(float value)
{

}

void ALylatArwing::OnMoveHorizontal(float value)
{

}

void ALylatArwing::OnTurn(float value)
{

}

void ALylatArwing::OnLookUp(float value)
{

}

FHitResult ALylatArwing::LaserTrace(const FVector& begin, const FVector& end) const
{
    FHitResult Hit(ForceInit);
    return Hit;
}