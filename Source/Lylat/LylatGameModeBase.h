// Copyright 2020 Project Lylat.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LylatGameModeBase.generated.h"

/**
 * Default Game mode.
 */
UCLASS() class LYLAT_API ALylatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()	
};

/**
 * On-Rails Shooter mode.
 */
UCLASS() class LYLAT_API ALylatGameModeOnRails : public ALylatGameModeBase
{
	GENERATED_BODY()
};

/**
 * 360° Movement mode.
 */
UCLASS() class LYLAT_API ALylatGameMode360 : public ALylatGameModeBase
{
	GENERATED_BODY()
};