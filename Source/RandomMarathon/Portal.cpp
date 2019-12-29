// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GamePlayerController.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EmptyObject = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Empty Object"));

	PortalEnter = this->CreateDefaultSubobject<UBoxComponent>(TEXT("Portal Enter"));
	PortalEnter->InitBoxExtent({ 50.0f, 250.0f, 100.0f });
	PortalEnter->SetCollisionProfileName(TEXT("Trigger"));
	PortalEnter->SetupAttachment(this->EmptyObject);
	PortalEnter->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);

	PortalExit = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal Exit"));
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (PortalExit)
		{
			auto controller = static_cast<AGamePlayerController*>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			controller->ChangeCharacter(PortalExit->GetComponentLocation());
		}
	}
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

