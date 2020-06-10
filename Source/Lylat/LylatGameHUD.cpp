// Copyright 2020 Team Project Lylat. All Rights Reserved.

#include "LylatGameHUD.h"
#include "LylatGameWidget.h"
#include "LylatPauseWidget.h"

#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/SWeakWidget.h"

void ALylatGameHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowHUD();
}

void ALylatGameHUD::ShowHUD()
{
	if (!GEngine || !GEngine->GameViewport) return;

	if (!HUDWidget.IsValid()) HUDWidget = SNew(SLylatGameWidget).OwningHUD(this);

	if (WidgetContainer.IsValid()) GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(HUDWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = false;
	PlayerOwner->SetInputMode(FInputModeGameOnly());
}

void ALylatGameHUD::ShowPause()
{
	if (!GEngine || !GEngine->GameViewport) return;
	
	if (!PauseWidget.IsValid()) PauseWidget = SNew(SLylatPauseWidget).OwningHUD(this);

	if (WidgetContainer.IsValid()) GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());	
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(PauseWidget.ToSharedRef()));

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}
