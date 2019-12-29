// Fill out your copyright notice in the Description page of Project Settings.

#include "RooollingCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARooollingCharacter::ARooollingCharacter() : Super()
{
	;
}

void ARooollingCharacter::NotifyHit(UPrimitiveComponent *MyComp, AActor *Other, UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Log, TEXT("NotifyHit"));
	Dead();
}

// Called when the game starts or when spawned
void ARooollingCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsSkillExist = false;
	IsAttackExist = false;

	AttackCoolDown = 10.0f;
	SkillCoolDown = 10.0f;

	SpeedRate = 1.5f;
	MaxHP = 1.0f;
	AttackingPower = 10.0f;

	CurrentHP = MaxHP;
}

// Called every frame
void ARooollingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float PitchValue = 0.f;
	PitchValue = ((GetVelocity().Size2D() / SpeedRate) * DeltaTime) * -1.f;
	FRotator NewRotation = FRotator(PitchValue, 0, 0);

	FQuat QuatRotation = FQuat(NewRotation);

	StaticMesh->AddRelativeRotation(QuatRotation);
}

// Called to bind functionality to input
void ARooollingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARooollingCharacter::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Log, TEXT("Rooolling Character : Attack"));
}

void ARooollingCharacter::Skill()
{
	Super::Skill();
	UE_LOG(LogTemp, Log, TEXT("Rooolling Character : Skill"));
}

void ARooollingCharacter::Dead()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FVector AttackLocation = GetActorLocation();

	AttackSphereRadius = 250.f;
	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		AttackLocation,
		AttackLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackSphereRadius),
		Params
	);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector();
	FVector Center = AttackLocation + TraceVec * AttackSphereRadius * 0.5f;
	float HalfHeight = AttackSphereRadius;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 0.5f;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackSphereRadius, CapsuleRot, DrawColor, false, DebugLifeTime);

#endif

	if (bResult)
	{
		if (HitResult.Actor.IsValid())
		{
			ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitResult.Actor);
			float dist = FVector::Dist2D(GetActorLocation(), HitCharacter->GetActorLocation());
			float damage = 200.f * (250-dist)/250.f;
			HitCharacter->AddDamage(damage);
			UE_LOG(LogTemp, Log, TEXT("Hit Actor Name : %s, Damage : %.2f"), *HitResult.Actor->GetName(), damage);
		}
	}
	Super::Dead();
}

