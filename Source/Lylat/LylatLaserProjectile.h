// Copyright 2020 Project Lylat. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatLaserProjectile.generated.h"

UCLASS(config=Game)
class LYLAT_API ALylatLaserProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Projectile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	ALylatLaserProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

protected:
	virtual void Tick(float delta) override;

public: 
	FORCEINLINE class UStaticMeshComponent* GetProjectile() const { return Projectile; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
