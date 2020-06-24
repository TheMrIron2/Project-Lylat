// Copyright (c) 2020 Team Project: Lylat. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish or distribute. This does not allow commercial distribution.
//
// This license does not cover any content made by Nintendo or any other commercial entity.
// Under this category fall the Arwing and the Wolfen model along with their respective assets, as well as the Star Fox trademark.
// Any commercial content has been used without permission.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "LylatDiscordComponent.h"

#include <chrono>

#define CLIENT_ID 725178546296979486

ULylatDiscordComponent::ULylatDiscordComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULylatDiscordComponent::BeginPlay()
{
	Super::BeginPlay();

	discord::Result result = discord::Core::Create(CLIENT_ID, DiscordCreateFlags_Default, &core);
	// TODO: check result

	discord::Activity activity{};
	activity.SetState("Map 1 [On-Rails]"); // TODO: Get map and game mode
	activity.GetAssets().SetLargeImage("lylat-logo"); // TODO: Set small image to logo and use large image for map screenshot

	activity.GetTimestamps().SetStart(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());

	// TODO: enhance usage of the Game SDK

	core->ActivityManager().UpdateActivity(activity, [](discord::Result result)
	{
		// TODO: check result
	});
}

void ULylatDiscordComponent::TickComponent(float delta, ELevelTick type, FActorComponentTickFunction* func)
{
	Super::TickComponent(delta, type, func);

	discord::Result result = core->RunCallbacks();
	// TODO: check result
}
