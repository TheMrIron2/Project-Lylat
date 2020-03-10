// Copyright (c) 2020 Project Lylat.

#include "LylatGameModeBase.h"
#include "LylatArwingController.h"

ALylatGameModeBase::ALylatGameModeBase()
{
	DefaultPawnClass = ALylatArwingController::StaticClass();
}
