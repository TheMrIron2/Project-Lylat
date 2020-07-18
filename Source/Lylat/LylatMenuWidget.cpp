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

#include "LylatMenuWidget.h"
#include "LylatMenuHUD.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "MenuLocalText"

void SLylatMenuWidget::Construct(const FArguments& inArgs)
{
	bCanSupportFocus	= true;
	OwningHUD			= inArgs._OwningHUD;

	const FMargin contentPadding	= FMargin(20.f, 10.f);
	const FMargin buttonPadding		= FMargin(10.f);

	const FText titleText			= LOCTEXT("GameTitle", "Project: Lylat");
	const FText startButtonText		= LOCTEXT("StartButton", "Start");
	const FText settingsButtonText	= LOCTEXT("SettingsButton", "Settings");
	const FText quitButtonText		= LOCTEXT("QuitButton", "Quit");

	FSlateFontInfo titleTextStyle	= FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleTextStyle.Size				= 90.f;

	FSlateFontInfo buttonTextStyle	= FCoreStyle::Get().GetFontStyle("EmbossedText");
	buttonTextStyle.Size			= 40.f;

	ChildSlot
	[
		SNew(SOverlay)

		// Backdrop
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::FromHex("000000")) // 23272A
		]

		// Widgets
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox)
			
			// Game Title
			+ SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(titleText)
				.Font(titleTextStyle)
				.Justification(ETextJustify::Left)
			]

			// Start Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatMenuWidget::OnStart)
				[
					SNew(STextBlock)
					.Text(startButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]

			// Settings Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatMenuWidget::OnSettings)
				[
					SNew(STextBlock)
					.Text(settingsButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]

			// Quit Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatMenuWidget::OnQuit)
				[
					SNew(STextBlock)
					.Text(quitButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
		]
	];
}

FReply SLylatMenuWidget::OnStart() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	UGameplayStatics::OpenLevel(OwningHUD->PlayerOwner, "Map1");
	return FReply::Handled();
}

FReply SLylatMenuWidget::OnSettings() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	OwningHUD->ShowSettings();

	return FReply::Handled();
}

FReply SLylatMenuWidget::OnQuit() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	OwningHUD->PlayerOwner->ConsoleCommand("quit");
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
