// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class MUNIZ_GAM415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	//Modifiable values of the procedural terrain
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int xSize = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int ySize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
		int zMultiplier = 0;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float noiseScale = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float terrainScale = 1.0f;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;

	UPROPERTY(EditAnywhere)
		float radius;

	UPROPERTY(EditAnywhere)
		FVector depth;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* mat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AlterMesh(FVector impactPoint);

private:

	//values depend on the public variables to create the mesh
	UProceduralMeshComponent* procMesh;
	TArray<FVector> vertices;
	TArray<int> triangles;
	TArray<FVector2D> UV0;
	TArray<FVector> normals;
	TArray<FColor> upVertexColors;

	int sectionID = 0;

	void CreateVertices();
	void CreateTriangles();

};
