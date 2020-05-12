// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameModeMenu.h"
#include "LylatArwing.h"
#include "LylatMenuHUD.h"
#include "UObject/ConstructorHelpers.h"

ALylatGameModeMenu::ALylatGameModeMenu()
{
	DefaultPawnClass = ALylatArwing::StaticClass();
    HUDClass = ALylatMenuHUD::StaticClass();
}
