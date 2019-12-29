// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ABaseCharacter;

enum DebuffType
{
	SLOW,
	HASTE,
	BURNING
};

class Debuff
{

public:
	Debuff();
	Debuff(FString DebuffName, float Duration, DebuffType BuffType, void(Function)(ABaseCharacter* Character));
	virtual ~Debuff();

	FString DebuffName;
	float Duration;
	DebuffType BuffType;

	virtual void CheckDebuffHasExpired(ABaseCharacter* Character, float DeltaTime);
	void (*AffectDebuffOnCharacter)(ABaseCharacter* Character);

};
