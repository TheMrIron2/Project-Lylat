// Copyright 2020 Project Lylat.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LylatArwingController.generated.h"

UCLASS()
class LYLAT_API ALylatArwingController : public ACharacter
{
	GENERATED_BODY()

public:
	ALylatArwingController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
