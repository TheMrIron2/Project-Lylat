// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LylatHUD.generated.h"

UCLASS()
class ALylatHUD : public AHUD
{
	GENERATED_BODY()

public:
	ALylatHUD();

	virtual void DrawHUD() override;

private:

};
