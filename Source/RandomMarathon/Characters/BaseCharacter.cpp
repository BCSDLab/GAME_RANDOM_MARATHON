// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"

#include "UObject/ConstructorHelpers.h"
#include "Collision.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "stdlib.h"

#include "DrawDebugHelpers.h"

#include "GamePlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	GetCapsuleComponent()->SetCollisionProfileName("MarathonCharacter");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	LastSpawnPos = GetActorLocation();

	RemainingAttackCoolDown = 0.0f;
	RemainingSkillCoolDown = 0.0f;

	AdditionalMaxHP = 0.0f;
	AdditionalSpeedRate = 1.0f;
	AdditionalAttackPower = 0.0f;
	AdditionalAttackPowerRate = 0.0f;

	AdditionalIsSkillPracticable = true;
	AdditionalIsAttackPracticable = true;

	IsInActivity = false;

	// 아래 주석까지의 내용은 상속한 캐릭터에서 재정의해야할 목록

	IsSkillExist = false;
	IsAttackExist = false;

	AttackCoolDown = 0.0f;
	SkillCoolDown = 0.0f;

	SpeedRate = 1.0f;
	MaxHP = 100.0f;
	AttackingPower = 10.0f;

	CurrentHP = MaxHP;

	//

	// 블루프린트 재정의를 허용하는 목록

	AttackSphereRadius = 50.f;
	AttackRange = 0.1f;

	//
}

#pragma region Tick

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckStatusEffectTimeHasExpired(DeltaTime);
	ReduceCoolDown(DeltaTime);
	CheckCharacterIsDead();
}

void ABaseCharacter::CheckCharacterIsDead()
{
	if (CurrentHP <= 0.0f)
	{
		Dead();
	}
}

void ABaseCharacter::CheckStatusEffectTimeHasExpired(float DeltaTime)
{
	AdditionalMaxHP = 0.0f;
	AdditionalSpeedRate = 1.0f;
	AdditionalAttackPower = 0.0f;
	AdditionalAttackPowerRate = 0.0f;
	AdditionalIsAttackPracticable = true;
	AdditionalIsSkillPracticable = true;

	for (auto Debuff : Debuffs)
	{
		Debuff.CheckDebuffHasExpired(this, DeltaTime);
	}
}

void ABaseCharacter::ReduceCoolDown(float DeltaTime)
{
	if (IsAttackExist)
	{
		RemainingAttackCoolDown -= DeltaTime;
		if (RemainingAttackCoolDown < 0.0f)
		{
			RemainingAttackCoolDown = 0.0f;
		}
	}

	if (IsSkillExist)
	{
		RemainingSkillCoolDown -= DeltaTime;
		if (RemainingSkillCoolDown < 0.0f)
		{
			RemainingSkillCoolDown = 0.0f;
		}
	}

}

#pragma endregion

#pragma region Debuff

void ABaseCharacter::AttachDebuff(Debuff newDebuff)
{
	bool IsAlreadyExist = false;
	for (auto Debuff : Debuffs)
	{
		if (Debuff.DebuffName.Equals(newDebuff.DebuffName))
		{
			Debuff.Duration = newDebuff.Duration;
			IsAlreadyExist = true;
		}
	}

	if (!IsAlreadyExist)
	{
		Debuffs.emplace_back(newDebuff);
	}
}

void ABaseCharacter::RemoveDebuff(FString DebuffName)
{
	for (std::vector<Debuff>::iterator Debuff = Debuffs.begin(); Debuff != Debuffs.end(); Debuff++)
	{
		if ((*Debuff).DebuffName.Equals(DebuffName))
		{
			Debuffs.erase(Debuff);
		}
	}
}

void ABaseCharacter::RemoveDebuff(DebuffType BuffType)
{
	for (std::vector<Debuff>::iterator Debuff = Debuffs.begin(); Debuff != Debuffs.end(); Debuff++)
	{
		if ((*Debuff).BuffType == BuffType)
		{
			Debuffs.erase(Debuff);
		}
	}

}


#pragma endregion

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ABaseCharacter::OnOverlapActivateSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ABaseCharacter* OtherCharacter = Cast<ABaseCharacter>(OtherActor);
		if (OtherCharacter)
		{
			OtherCharacter->AddDamage(AttackingPower);
		}
	}
}

void ABaseCharacter::Attack()
{
	IsInActivity = true;
	UE_LOG(LogTemp, Log, TEXT("BaseMarathonCharacter : Attack"));
	RemainingAttackCoolDown = AttackCoolDown;

	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	FVector AttackLocation = GetActorLocation() + GetActorForwardVector() * AttackStartRelativePosition.X + FVector(0,0,AttackStartRelativePosition.Z);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		AttackLocation,
		AttackLocation + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AttackSphereRadius),
		Params
	);


#if ENABLE_DRAW_DEBUG

	FVector TraceVec = GetActorForwardVector() * AttackRange;
	FVector Center = AttackLocation + TraceVec * AttackSphereRadius * 0.5f;
	float HalfHeight = AttackRange * 0.5f + AttackSphereRadius;
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
			HitCharacter->AddDamage(GetCurrentDamage());
			UE_LOG(LogTemp, Log, TEXT("Hit Actor Name : %s"), *HitResult.Actor->GetName());
		}
	}

}

void ABaseCharacter::Skill()
{
	UE_LOG(LogTemp, Log, TEXT("BaseMarathonCharacter : Attack"));
	RemainingSkillCoolDown = SkillCoolDown;
}

void ABaseCharacter::Dead()
{
	if (GetWorld()->GetFirstPlayerController())
	{	
		if (GetWorld()->GetFirstPlayerController()->GetCharacter()->GetUniqueID() == GetUniqueID())
		{
			(Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController()))->Respawn();
		}
		else 
		{
			Destroy();
		}
	}
	else 
	{
		Destroy();
	}
}