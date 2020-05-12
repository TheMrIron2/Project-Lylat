// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class LYLAT_API SLylatMenuWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLylatMenuWidget) { }

    SLATE_ARGUMENT(TWeakObjectPtr<class ALylatMenuHUD>, OwningHUD)

    SLATE_END_ARGS()
    
    void Construct(const FArguments& inArgs);

    TWeakObjectPtr<class ALylatMenuHUD> OwningHUD;

    virtual bool SupportsKeyboardFocus() const override { return true; }
};