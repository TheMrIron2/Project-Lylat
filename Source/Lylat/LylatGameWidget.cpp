// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatGameWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "HUDText"

void SLylatGameWidget::Construct(const FArguments& inArgs)
{
	bCanSupportFocus = true;
	OwningHUD = inArgs._OwningHUD;

	ChildSlot
	[
		SNew(SOverlay)
	];
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION