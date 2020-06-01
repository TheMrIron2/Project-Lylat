// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameModeOnRails.h"
#include "LylatArwing.h"
#include "LylatGameHUD.h"

#include "UObject/ConstructorHelpers.h"

ALylatGameModeOnRails::ALylatGameModeOnRails()
{
	DefaultPawnClass = ALylatArwing::StaticClass();
    HUDClass = ALylatGameHUD::StaticClass();
}
