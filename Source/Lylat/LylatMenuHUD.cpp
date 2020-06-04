// Copyright 2020 Project Lylat. All Rights Reserved.

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

	if (!PlayerOwner) return;

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void ALylatMenuHUD::SwitchToMap(const FString& url)
{
	PlayerOwner->GetWorld()->ServerTravel(url, true, false);
}

void ALylatMenuHUD::QuitGame()
{
	PlayerOwner->ConsoleCommand("quit");
}