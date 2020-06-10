// Copyright 2020 Team Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

template <typename T>
static FORCEINLINE T* LylatGetResource(const TCHAR* path)
{
    if (path == NULL) return NULL;
    return Cast<T>(StaticLoadObject(T::StaticClass(), NULL, path));
}
