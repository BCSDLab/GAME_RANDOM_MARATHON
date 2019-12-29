
#include "TrexCharacter.h"
#include "GameFramework/PlayerController.h"


// Sets default values
ATrexCharacter::ATrexCharacter() : Super()
{
	;
}

// Called when the game starts or when spawned
void ATrexCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsSkillExist = true;
	IsAttackExist = true;

	AttackCoolDown = 10.0f;
	SkillCoolDown = 10.0f;

	SpeedRate = 0.5f;
	MaxHP = 100.0f;
	AttackingPower = 10.0f;

	CurrentHP = MaxHP;
}

// Called every frame
void ATrexCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrexCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATrexCharacter::Attack()
{
	Super::Attack();
	UE_LOG(LogTemp, Log, TEXT("Trex Character : Attack"));
}

void ATrexCharacter::Skill()
{
	Super::Skill();
	UE_LOG(LogTemp, Log, TEXT("Trex Character : Skill"));
}
