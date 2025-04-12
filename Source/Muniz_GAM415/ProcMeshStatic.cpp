// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcMeshStatic.h"
#include "KismetProceduralMeshLibrary.h"
#include "StaticMeshOperations.h"

// Sets default values
AProcMeshStatic::AProcMeshStatic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	procMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));

	//set procMesh to Root Component
	RootComponent = procMesh;
	baseMesh->SetupAttachment(procMesh);

}

// Called when the game starts or when spawned
void AProcMeshStatic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProcMeshStatic::PostActorCreated()
{
	Super::PostActorCreated();
	GetMeshData();
}

void AProcMeshStatic::PostLoad()
{
	Super::PostLoad();
	GetMeshData();
}

// Called every frame
void AProcMeshStatic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProcMeshStatic::AlterMesh(FVector impactPoint)
{
	for (int i = 0; i < Vertices.Num(); i++)
	{
		FVector tempVector = impactPoint - this->GetActorLocation();

		if (FVector(Vertices[i] - tempVector).Size())
		{
			procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, upVertexColors, TArray<FProcMeshTangent>());
		}
	}
	
}

//Assigns procMesh data
void AProcMeshStatic::GetMeshData()
{
	UStaticMesh* mesh = baseMesh->GetStaticMesh();
	if (mesh)
	{
		UKismetProceduralMeshLibrary::GetSectionFromStaticMesh(mesh, 0, 0, Vertices, Triangles, Normals, UV0, tangents);
		procMesh->UpdateMeshSection(0, Vertices, Normals, UV0, upVertexColors, tangents);
		CreateMesh();
		
	}
}

//Creates procMesh if baseMesh is assigned
void AProcMeshStatic::CreateMesh()
{
	if (baseMesh)
	{
		procMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, upVertexColors, tangents, true);
	}
}

