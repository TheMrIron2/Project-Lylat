// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LylatMenuHUD.generated.h"

UCLASS()
class LYLAT_API ALylatMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	TSharedPtr<class SLylatMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
};
