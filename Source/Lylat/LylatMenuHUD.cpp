// Copyright 2020 Team Project Lylat. All Rights Reserved.

#include "LylatMenuHUD.h"
#include "LylatMenuWidget.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Widgets/SWeakWidget.h"

void ALylatMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!GEngine || !GEngine->GameViewport) return;

	MenuWidget = SNew(SLylatMenuWidget).OwningHUD(this);
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

	MenuWidget->SetVisibility(EVisibility::Visible);

	if (!PlayerOwner) return;

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}
