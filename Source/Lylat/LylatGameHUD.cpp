// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameHUD.h"
#include "LylatGameWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void ALylatGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GEngine || !GEngine->GameViewport) return;

	MenuWidget = SNew(SLylatGameWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
}
