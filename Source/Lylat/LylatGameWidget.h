// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class LYLAT_API SLylatGameWidget : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SLylatGameWidget) { }

    SLATE_ARGUMENT(TWeakObjectPtr<class ALylatGameHUD>, OwningHUD)

    SLATE_END_ARGS()
    
    void Construct(const FArguments& inArgs);

    TWeakObjectPtr<class ALylatGameHUD> OwningHUD;

    virtual bool SupportsKeyboardFocus() const override { return true; }
};