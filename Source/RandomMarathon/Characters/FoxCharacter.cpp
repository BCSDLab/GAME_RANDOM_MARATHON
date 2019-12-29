// Fill out your copyright notice in the Description page of Project Settings.

#include "FoxCharacter.h"

AFoxCharacter::AFoxCharacter() : Super()
{
	;
}

// Called when the game starts or when spawned
void AFoxCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsSkillExist = true;
	IsAttackExist = true;

	AttackCoolDown = 3.0f;
	SkillCoolDown = 15.0f;

	SpeedRate = 1.2f;
	MaxHP = 70.0f;
	AttackingPower = 10.0f;

	CurrentHP = MaxHP;

	AttackStartRelativePosition = FVector(70.f, 0.f, -30.f);
	AttackSphereRadius = 45.f;
	AttackRange = 0.1f;

}

// Called every frame
void AFoxCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFoxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AFoxCharacter::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Log, TEXT("FoxCharacter : Attack"));
}

void AFoxCharacter::Skill()
{
	Super::Skill();
	UE_LOG(LogTemp, Log, TEXT("FoxCharacter : Skill"));
}
