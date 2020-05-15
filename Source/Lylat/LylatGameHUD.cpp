// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameHUD.h"
#include "LylatGameWidget.h"
#include "LylatPauseWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"

void ALylatGameHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowHUD();
}

void ALylatGameHUD::ShowHUD()
{
	if (!GEngine || !GEngine->GameViewport) return;

	GEngine->GameViewport->RemoveAllViewportWidgets();

	HUDWidget = SNew(SLylatGameWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(HUDWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void ALylatGameHUD::ShowPause()
{
	if (!GEngine || !GEngine->GameViewport) return;
	
	GEngine->GameViewport->RemoveAllViewportWidgets();

	PauseWidget = SNew(SLylatPauseWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(PauseWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}