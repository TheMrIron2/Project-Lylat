// Copyright 2020 Team Project Lylat. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

class LYLAT_API SLylatPauseWidget : public SCompoundWidget
{
protected:
    SLATE_BEGIN_ARGS(SLylatPauseWidget) { }

    SLATE_ARGUMENT(TWeakObjectPtr<class ALylatGameHUD>, OwningHUD)

    SLATE_END_ARGS()
    
    void Construct(const FArguments& inArgs);

    FReply OnResume() const;

    TWeakObjectPtr<class ALylatGameHUD> OwningHUD;

    virtual bool SupportsKeyboardFocus() const override { return true; }
};
