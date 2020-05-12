// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatMenuHUD.h"
#include "LylatMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void ALylatMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GEngine || !GEngine->GameViewport) return;

	MenuWidget = SNew(SLylatMenuWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));
}
