// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Sets the procMesh as the rootcomponent
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	procMesh->SetupAttachment(GetRootComponent());
	
	
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	//Creates the mesh at runtime
	CreateVertices();
	CreateTriangles();
	procMesh->CreateMeshSection(sectionID, vertices, triangles, normals, UV0, upVertexColors, TArray<FProcMeshTangent>(), true);
	procMesh->SetMaterial(0, mat);
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


//This allows us to alter the terrain when another actor comes into contact with it. Like a projectile for example.
void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(vertices[i] - tempVector).Size() > radius)
		{
			vertices[i] = vertices[i] - depth;
			procMesh->UpdateMeshSection(sectionID, vertices, normals, UV0, upVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	for (int X = 0; X <= xSize; X++)
	{
		for (int Y = 0; Y <= ySize; Y++)
		{
			float z = FMath::PerlinNoise2D(FVector2D(X * noiseScale + 0.1, Y * noiseScale + 0.1)) * zMultiplier;
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), z));
			vertices.Add(FVector(X * terrainScale, Y * terrainScale, z));
			UV0.Add(FVector2D(X + UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int vertex = 0;
	for (int X = 0; X <= xSize; X++)
	{
		for (int Y = 0; Y <= ySize; Y++)
		{
			triangles.Add(vertex);
			triangles.Add(vertex + 1);
			triangles.Add(vertex + ySize + 1);
			triangles.Add(vertex + 1);
			triangles.Add(vertex + ySize + 2);
			triangles.Add(vertex + ySize + 1);

			vertex++;
		}
	}
}

