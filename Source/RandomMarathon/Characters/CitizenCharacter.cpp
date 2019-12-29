// Fill out your copyright notice in the Description page of Project Settings.

#include "CitizenCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprintGeneratedClass.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/AnimInstance.h"
#include "Components/MeshComponent.h"
#include "Collision.h"

#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "stdlib.h"
// Sets default values

ACitizenCharacter::ACitizenCharacter() : Super()
{
	;
}

// Called when the game starts or when spawned
void ACitizenCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsSkillExist = false;
	IsAttackExist = true;

	AttackCoolDown = 10.0f;
	SkillCoolDown = 10.0f;

	SpeedRate = 0.7f;
	MaxHP = 100.0f;
	AttackingPower = 10.0f;

	CurrentHP = MaxHP;

	AttackStartRelativePosition = FVector(40.f, 0.f, 0.f);
	AttackSphereRadius = 60.f;
}

// Called every frame
void ACitizenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACitizenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACitizenCharacter::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Log, TEXT("HumanCharacter : Attack"));
}

void ACitizenCharacter::Skill()
{
	Super::Skill();
	UE_LOG(LogTemp, Log, TEXT("HumanCharacter : Skill"));
}
