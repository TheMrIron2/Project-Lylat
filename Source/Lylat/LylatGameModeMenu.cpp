// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameModeMenu.h"
#include "LylatMenuHUD.h"
#include "UObject/ConstructorHelpers.h"

ALylatGameModeMenu::ALylatGameModeMenu()
{
    HUDClass = ALylatMenuHUD::StaticClass();
}
