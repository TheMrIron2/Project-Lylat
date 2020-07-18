// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by any commercial entity.
//
// Under the category "content used without permission" falls any content regarding the "Star Fox" trademark.
// Star Fox is a registered trademark of Nintendo Co., Ltd.
// 
// Under the category "content used according to licensing" fall the Discord Game SDK and the Ultralight SDK.
// Discord is a registered trademark of Discord, Inc.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "LylatMenuHUD.h"
#include "LylatMenuWidget.h"
#include "LylatSettingsWidget.h"

#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Widgets/SWeakWidget.h"

void ALylatMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowMenu();

	if (!PlayerOwner) return;

	PlayerOwner->bShowMouseCursor = true;
	PlayerOwner->SetInputMode(FInputModeUIOnly());
}

void ALylatMenuHUD::ShowMenu()
{
	if (!GEngine || !GEngine->GameViewport) return;
	if (!MenuWidget.IsValid()) MenuWidget = SNew(SLylatMenuWidget).OwningHUD(this);

	if (WidgetContainer.IsValid()) GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef()));

	MenuWidget->SetVisibility(EVisibility::Visible);
}

void ALylatMenuHUD::ShowSettings()
{
	if (!GEngine || !GEngine->GameViewport) return;

	if (!SettingsWidget.IsValid()) SettingsWidget = SNew(SLylatSettingsWidget).OwningHUD(this);

	if (WidgetContainer.IsValid()) GEngine->GameViewport->RemoveViewportWidgetContent(WidgetContainer.ToSharedRef());
	GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(WidgetContainer, SWeakWidget).PossiblyNullContent(SettingsWidget.ToSharedRef()));

	SettingsWidget->SetVisibility(EVisibility::Visible);
}

