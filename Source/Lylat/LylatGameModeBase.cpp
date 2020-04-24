// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameModeBase.h"
#include "LylatArwing.h"
#include "LylatHUD.h"
#include "UObject/ConstructorHelpers.h"

ALylatGameModeBase::ALylatGameModeBase()
{
	DefaultPawnClass = ALylatArwing::StaticClass();
    HUDClass = ALylatHUD::StaticClass();
}
