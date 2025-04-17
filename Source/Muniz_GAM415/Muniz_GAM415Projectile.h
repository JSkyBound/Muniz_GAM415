// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Muniz_GAM415Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS(config=Game)
class AMuniz_GAM415Projectile : public AActor
{
	GENERATED_BODY()
	

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
		UMaterial* baseMaterial;

	UPROPERTY()
		FLinearColor randColor;

	UPROPERTY(EditAnywhere)
		UMaterialInterface* projectileMaterial;

	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* colorParticle;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* muzzleSpark;
public:
	AMuniz_GAM415Projectile();
protected:
	virtual void BeginPlay();

public:
	
	UPROPERTY()
	bool isTeleporting;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

