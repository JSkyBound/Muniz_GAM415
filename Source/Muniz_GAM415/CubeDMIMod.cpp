// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "Muniz_GAM415Character.h"
#include "Chaos/Deformable/ChaosDeformableCollisionsProxy.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));

	RootComponent = boxComp;
	baseMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

	if(baseMat)
	{
		dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
	}

	if (baseMesh)
	{
		baseMesh->SetMaterial(0, dmiMat);
	}
	
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACubeDMIMod::OnOverlapBegin(class UPrimitiveComponent* overlappedComp, class AActor* otherActor,
	class UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	AMuniz_GAM415Character* overlappedActor = Cast<AMuniz_GAM415Character>(otherActor);

	if (overlappedActor)
	{
		float randNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float randNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
		float randNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

		FVector4 randColor = FVector4(randNumX, randNumY, randNumZ, 1.f);
		if (dmiMat)
		{
			dmiMat->SetVectorParameterValue("Color", randColor);
			dmiMat->SetScalarParameterValue("Darkness", randNumX);
			dmiMat->SetScalarParameterValue("Opacity", randNumY);
		}

	}
}

