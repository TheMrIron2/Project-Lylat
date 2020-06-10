// Copyright 2020 Team Project Lylat. All Rights Reserved.

#include "LylatPauseWidget.h"
#include "LylatGameHUD.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "PauseMenuText"

void SLylatPauseWidget::Construct(const FArguments& inArgs)
{
	bCanSupportFocus = true;
	OwningHUD = inArgs._OwningHUD;
	
	const FMargin contentPadding = FMargin(20.f, 10.f);
	const FMargin buttonPadding = FMargin(10.f);

	const FText pauseTitleText = LOCTEXT("PauseTitle", "Paused");
	const FText resumeButtonText = LOCTEXT("ResumeButton", "Resume");

	FSlateFontInfo pauseTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	pauseTextStyle.Size = 190.f;

	FSlateFontInfo buttonTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	buttonTextStyle.Size = 40.f;

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(pauseTitleText)
				.Font(pauseTextStyle)
				.Justification(ETextJustify::Left)
			]
		]

		// Widgets
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox)

			// Resume Button
			+ SVerticalBox::Slot()
			.Padding(buttonPadding)
			[
				SNew(SButton)
				.OnClicked(this, &SLylatPauseWidget::OnResume)
				[
					SNew(STextBlock)
					.Text(resumeButtonText)
					.Font(buttonTextStyle)
					.Justification(ETextJustify::Center)
				]
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
			]
		]
	];
}

FReply SLylatPauseWidget::OnResume() const
{
	if (!OwningHUD.IsValid()) return FReply::Handled();

	OwningHUD->ShowHUD();
	OwningHUD->PlayerOwner->Pause();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
