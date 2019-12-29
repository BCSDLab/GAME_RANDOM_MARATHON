// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trap.h"
#include "Characters/BaseCharacter.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = this->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
	Buff.DebuffName = "TRAP_SLOW";
	Buff.Duration = 10.0f;
	Buff.BuffType = DebuffType::SLOW;
	Buff.AffectDebuffOnCharacter = [](ABaseCharacter* Character) { Character->AdditionalSpeedRate *= 0.5f; };

}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABaseCharacter* OtherCharacter = Cast<ABaseCharacter>(OtherActor);
	if (OtherCharacter) 
	{
		OtherCharacter->AttachDebuff(Debuff(FString("TRAP_SLOW"), 10.0f, DebuffType::SLOW, ([](ABaseCharacter* Character) {
			Character->AdditionalSpeedRate *= 0.5f;})));
	}
}


