// Copyright 2020 Project Lylat. All Rights Reserved.

#include "LylatHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Texture2D.h"

float to_float(uint8_t x)
{
    uint32_t out = 0x3f800000 + x * 0x8080;
    return (float &)out + 256 - 257;
}

typedef struct texLoader
{
    ConstructorHelpers::FObjectFinderOptional<UTexture2D> Texture;
    texLoader(const TCHAR* path) : Texture(path) { }
} texLoader;

ALylatHUD::ALylatHUD()
{
	Crosshair	= texLoader(TEXT("/Game/Textures/HUD/Crosshair.Crosshair")).Texture.Get();
	BoostMeter	= texLoader(TEXT("/Game/Textures/HUD/BoostMeter.BoostMeter")).Texture.Get();
	BoostLevel	= texLoader(TEXT("/Game/Textures/HUD/BoostLevel.BoostLevel")).Texture.Get();
}

void ALylatHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D BoostMeterDrawPosition(Center.X + Center.X - 150.f, 10.f);
	const FVector2D CrosshairDrawPosition(Center.X - 5.f, Center.Y - 5.f);

	FCanvasTileItem BoostMeterTile(BoostMeterDrawPosition, BoostMeter->Resource, FLinearColor::White);
	BoostMeterTile.BlendMode = SE_BLEND_Translucent;

	FCanvasTileItem CrosshairTile(CrosshairDrawPosition, Crosshair->Resource, FLinearColor(to_float(22), to_float(229), to_float(247)));
	CrosshairTile.BlendMode = SE_BLEND_Translucent;

	Canvas->DrawItem(BoostMeterTile);
	Canvas->DrawItem(CrosshairTile);
}
