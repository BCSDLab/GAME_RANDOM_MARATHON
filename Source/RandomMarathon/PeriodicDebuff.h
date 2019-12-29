// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Debuff.h"
#include "CoreMinimal.h"

/**
 * 
 */
class RANDOMMARATHON_API PeriodicDebuff : Debuff
{
private:

	float RestPeriod;
public:

	float Period;

	PeriodicDebuff();
	PeriodicDebuff(FString DebuffName, float Duration, DebuffType BuffType, void(Function)(ABaseCharacter* Character), float Period = 1.0f);
	~PeriodicDebuff();

	virtual void CheckDebuffHasExpired(ABaseCharacter* Character, float DeltaTime);
};
