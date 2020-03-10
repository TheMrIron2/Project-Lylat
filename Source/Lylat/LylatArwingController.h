// Copyright (c) 2020 Project Lylat.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatArwingController.generated.h"

UCLASS(Config=Game)
class ALylatArwingController : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArwingMesh;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	ALylatArwingController();

	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* Component, class AActor* Other, class UPrimitiveComponent* OtherComponent, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void SpeedInput(float Value);
	void VerticalInput(float Value);
	void HorizontalInput(float Value);

private:
	UPROPERTY(Category = Properties, EditAnywhere)
	float Acceleration;

	UPROPERTY(Category = Properties, EditAnywhere)
	float TurnSpeed;

	UPROPERTY(Category = Properties, EditAnywhere)
	float MaxSpeed;

	UPROPERTY(Category = Properties, EditAnywhere)
	float MinSpeed;

	float CurrentForwardSpeed;
	float CurrentYawSpeed;
	float CurrentPitchSpeed;
	float CurrentRollSpeed;

public:
	FORCEINLINE class UStaticMeshComponent* GetArwingMesh() const { return ArwingMesh; }
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
