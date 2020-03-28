// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameModeBase.h"
#include "LylatArwing.h"
#include "LylatHUD.h"
#include "UObject/ConstructorHelpers.h"

ALylatGameModeBase::ALylatGameModeBase()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/")); // TODO: add path to data
	DefaultPawnClass = PlayerPawnClassFinder.Class;

    HUDClass = ALylatHUD::StaticClass();
}