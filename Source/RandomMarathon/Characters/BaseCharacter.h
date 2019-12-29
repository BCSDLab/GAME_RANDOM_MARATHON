// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Debuff.h"

#include "vector"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"

#include "BaseCharacter.generated.h"

UCLASS()
class RANDOMMARATHON_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsSkillExist;
	bool IsAttackExist;
	bool IsInActivity;

	float AttackCoolDown;
	float SkillCoolDown;

	float RemainingAttackCoolDown;
	float RemainingSkillCoolDown;

	float MaxHP;
	float SpeedRate;
	float AttackingPower;
	
	UPROPERTY(Category = Status, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float CurrentHP;

	FVector LastSpawnPos;
	FVector MovementVector;

	UPROPERTY(Category = Attack, VisibleAnywhere, BlueprintReadWrite)
	FVector AttackStartRelativePosition;

	UPROPERTY(Category = Attack, VisibleAnywhere, BlueprintReadWrite)
	float AttackSphereRadius;

	UPROPERTY(Category = Attack, VisibleAnywhere, BlueprintReadWrite)
	float AttackRange;

public:

	float AdditionalMaxHP;
	float AdditionalSpeedRate;
	float AdditionalAttackPower;
	float AdditionalAttackPowerRate;
	bool AdditionalIsSkillPracticable;
	bool AdditionalIsAttackPracticable;

protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

private:

	// TArray<Debuff> Debuffs;
	std::vector<Debuff> Debuffs;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Getter")
		bool GetIsSkillExist() { return IsSkillExist; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		bool GetIsAttackExist() { return IsAttackExist; }

	UFUNCTION(BlueprintCallable, Category = "Getter")
		bool GetIsSkillPracticable() { return AdditionalIsSkillPracticable; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		bool GetIsAttackPracticable() { return AdditionalIsAttackPracticable; }

	UFUNCTION(BlueprintCallable, Category = "Getter")
		FVector GetLastSpawnPos() { return LastSpawnPos; }

	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetSpeedRate() { return SpeedRate; };
	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetMaxHP() { return MaxHP + AdditionalMaxHP; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetCurrentHP() { return CurrentHP; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetCurrentSpeedRate() { return SpeedRate * AdditionalSpeedRate; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetCurrentDamage() { return ((AttackingPower + AdditionalAttackPower) * (1.0f + AdditionalAttackPowerRate)); }

	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetRemainingAttackCoolDown() { return RemainingAttackCoolDown; }
	UFUNCTION(BlueprintCallable, Category = "Getter")
		float GetRemainingSkillCoolDown() { return RemainingSkillCoolDown; }

	UFUNCTION(BlueprintCallable, Category = "Setter")
		void SetLastSpawnPos(FVector lastspawnpos) { LastSpawnPos = lastspawnpos; }

	UFUNCTION(BlueprintCallable, Category = "Checker")
		void CheckCharacterIsDead();

	UFUNCTION(BlueprintCallable, Category = "Checker")
		void CheckStatusEffectTimeHasExpired(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Timer")
		void ReduceCoolDown(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Battle")
		void AddHealth(float health) { CurrentHP += health; if (CurrentHP > MaxHP) CurrentHP = MaxHP; };

	UFUNCTION(BlueprintCallable, Category = "Battle")
		void AddDamage(float damage) { CurrentHP -= damage; };

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void OnOverlapActivateSphere(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void AttachDebuff(Debuff newDebuff);
	void RemoveDebuff(FString DebuffName);
	void RemoveDebuff(DebuffType BuffType);

	// 아래 두 함수를 상속해서 캐릭터를 만들때엔 '반드시' 부모의 함수를 호출할 것.

	UFUNCTION(BlueprintCallable, Category = "PlayerAction")
		virtual void Attack();

	UFUNCTION(BlueprintCallable, Category = "PlayerAction")
		virtual void Skill();

	UFUNCTION(BlueprintCallable, Category = "PlayerAction")
		virtual void Dead();

};
