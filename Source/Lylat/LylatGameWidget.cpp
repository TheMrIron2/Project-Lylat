// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameWidget.h"

#define LOCTEXT_NAMESPACE "HUDText"

void SLylatGameWidget::Construct(const FArguments& inArgs)
{
	ChildSlot
	[
		SNew(SOverlay)
	];
}

#undef LOCTEXT_NAMESPACE