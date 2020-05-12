// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameWidget.h"

#define LOCTEXT_NAMESPACE "GameTexts"

void SLylatGameWidget::Construct(const FArguments& inArgs)
{
	const FMargin contentPadding = FMargin(500.f, 300.f);
	const FText statusText = LOCTEXT("StatusMessage", "owo");

	ChildSlot
	[
		SNew(SOverlay) + SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Top)
		[
			SNew(SImage)
			.ColorAndOpacity(FColor::Black)
		]
		+ SOverlay::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(contentPadding)
		[
			SNew(SVerticalBox) + SVerticalBox::Slot()
			[
				SNew(STextBlock)
				.Text(statusText)
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE