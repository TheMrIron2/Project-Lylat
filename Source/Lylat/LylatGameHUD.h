// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LylatGameHUD.generated.h"

UCLASS()
class LYLAT_API ALylatGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<class SLylatGameWidget> HUDWidget;
	TSharedPtr<class SLylatPauseWidget> PauseWidget;
	TSharedPtr<class SWidget> WidgetContainer;
	
	virtual void BeginPlay() override;

public:
	void ShowHUD();
	void ShowPause();
};
