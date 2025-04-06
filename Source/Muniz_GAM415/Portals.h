// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/ArrowComponent.h"
#include "Portals.generated.h"


class AMuniz_GAM415Character;

UCLASS()
class MUNIZ_GAM415_API APortals : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PortalMesh;

	UPROPERTY(EditAnywhere)
		UArrowComponent* RootArrow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* SceneCapture;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* RenderTarget;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere)
	APortals* OtherPortal;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetBool(AMuniz_GAM415Character* PlayerChar);

	UFUNCTION()
	void UpdatePortals();
	

};
