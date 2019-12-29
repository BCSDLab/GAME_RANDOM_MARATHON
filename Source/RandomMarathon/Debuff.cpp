// Fill out your copyright notice in the Description page of Project Settings.

#include "Debuff.h"
#include "Characters/BaseCharacter.h"


Debuff::Debuff()
{

}

Debuff::Debuff(FString NewDebuffName, float NewDuration, DebuffType NewBuffType, void (Function)(ABaseCharacter* Character))
{
	DebuffName = NewDebuffName;
	Duration = NewDuration;
	BuffType = NewBuffType;
	AffectDebuffOnCharacter = Function;
}

Debuff::~Debuff()
{

}

void Debuff::CheckDebuffHasExpired(ABaseCharacter* Character, float DeltaTime)
{
	AffectDebuffOnCharacter(Character);
	UE_LOG(LogTemp, Log, TEXT("Debuff!!!!!!! :: %f"), Duration);

	Duration -= DeltaTime;
	if (Duration < 0.0f)
	{
		Character->RemoveDebuff(DebuffName);
	}
}