// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatMenuWidget.h"
#include "LylatMenuHUD.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "MenuLocalText"

void SLylatMenuWidget::Construct(const FArguments& inArgs)
{
	bCanSupportFocus = true;
	OwningHUD = inArgs._OwningHUD;

	const FMargin contentPadding = FMargin(20.f, 10.f);
	const FMargin buttonPadding = FMargin(10.f);

	const FText titleText = LOCTEXT("GameTitle", "Project: Lylat");
	const FText startButtonText = LOCTEXT("StartButton", "Start");
	const FText settingsButtonText = LOCTEXT("SettingsButton", "Settings");
	const FText quitButtonText = LOCTEXT("QuitButton", "Quit");

	FSlateFontInfo titleTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	titleTextStyle.Size = 90.f;

	FSlateFontInfo buttonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	buttonTextStyle.Size = 40.f;

	ChildSlot
	[
		SNew(SOverlay)

		// Backdrop
		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::FromHex("#23272A"))
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
