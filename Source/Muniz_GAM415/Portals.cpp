// Fill out your copyright notice in the Description page of Project Settings.


#include "Portals.h"
#include "Muniz_GAM415Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortals::APortals()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));

	RootComponent = BoxComp;
	PortalMesh->SetupAttachment(BoxComp);
	SceneCapture->SetupAttachment(PortalMesh);

	PortalMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	

}

// Called when the game starts or when spawned
void APortals::BeginPlay()
{
	Super::BeginPlay();
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APortals::OnOverlapBegin);
	PortalMesh->SetHiddenInSceneCapture(true);

	if (mat)
	{
		PortalMesh->SetMaterial(0, mat);
	}
	
}

// Called every frame
void APortals::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortals::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMuniz_GAM415Character* PlayerChar = Cast<AMuniz_GAM415Character>(OtherActor);
	if (PlayerChar)
	{
		if (OtherPortal)
		{
			if (!PlayerChar->isTeleporting)
			{
				PlayerChar->isTeleporting = true;
				FVector loc = OtherPortal->GetActorLocation();
				PlayerChar->SetActorLocation(loc);

				FTimerHandle TimerHandle;
				FTimerDelegate TimerDel;
				TimerDel.BindUFunction(this, "SetBool", PlayerChar);
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 1, false);
			}
		}
	}
}

void APortals::SetBool(AMuniz_GAM415Character* PlayerChar)
{
	if (PlayerChar)
	{
		PlayerChar->isTeleporting = false;
	}
}

void APortals::UpdatePortals()
{
	FVector Location = this->GetActorLocation() - OtherPortal->GetActorLocation();
	FVector CamLocation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentLocation();
	FRotator CamRotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentRotation();
	FVector CombinedLocation = Location + CamLocation;

	SceneCapture->SetWorldLocationAndRotation(CombinedLocation, CamRotation);

}

