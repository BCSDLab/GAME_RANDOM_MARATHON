// Fill out your copyright notice in the Description page of Project Settings.

#include "PeriodicDebuff.h"
#include "Characters/BaseCharacter.h"

PeriodicDebuff::PeriodicDebuff()
{
}

PeriodicDebuff::PeriodicDebuff(FString NewDebuffName, float NewDuration, DebuffType NewBuffType, void(Function)(ABaseCharacter* Character), float NewPeriod)
{
	DebuffName = NewDebuffName;
	Duration = NewDuration;
	BuffType = NewBuffType;
	AffectDebuffOnCharacter = Function;
	Period = NewPeriod;
	RestPeriod = NewPeriod;
}

PeriodicDebuff::~PeriodicDebuff()
{
}

void PeriodicDebuff::CheckDebuffHasExpired(ABaseCharacter* Character, float DeltaTime)
{
	RestPeriod -= DeltaTime;
	if (RestPeriod < 0.0f) 
	{
		AffectDebuffOnCharacter(Character);
		RestPeriod = Period;
	}

	Duration -= DeltaTime;
	if (Duration < 0.0f)
	{
		Character->RemoveDebuff(DebuffName);
	}
}