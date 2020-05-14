// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatPauseWidget.h"

#define LOCTEXT_NAMESPACE "PauseMenuText"

void SLylatPauseWidget::Construct(const FArguments& inArgs)
{
	const FMargin contentPadding = FMargin(20.f, 10.f);
	const FText pauseTitleText = LOCTEXT("PauseTitle", "Paused");

	FSlateFontInfo pauseTextStyle = FCoreStyle::Get().GetFontStyle("EmbossedText");
	pauseTextStyle.Size = 190.f;

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
	];
}

#undef LOCTEXT_NAMESPACE