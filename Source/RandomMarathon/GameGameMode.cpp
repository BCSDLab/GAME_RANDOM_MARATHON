// Fill out your copyright notice in the Description page of Project Settings.

#include "GameGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

AGameGameMode::AGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGameGameMode::StaticClass();
	
	// DefaultPawnClass = Characters[SelectCharacterRandomly()];
	
	CurrentNumberLanes = 0;

}

void AGameGameMode::CountLanes(int Number)
{
	CurrentNumberLanes += Number;

	if (CurrentNumberLanes >= TargetNumberLanes)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Main");
	}
}

void AGameGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

/* 캐릭터 스폰을 GameMode에서 관리해야할지 확신이 서지 않아 임시적으로 작성해놓은 코드.

APawn* AGameGameMode::SpawnMarathonCharacter(int Order, FVector NewPos)
{
	ABaseMarathonCharacter* RetPawn;
	RetPawn = GetWorld()->SpawnActor<ABaseMarathonCharacter>(Characters[Order], NewPos, FRotator::ZeroRotator);
	return RetPawn;
}

int AGameGameMode::SelectCharacterRandomly() 
{
	static FRandomStream* randstream = new FRandomStream();
	
	randstream->FRandRange(0.0, 1.0f);
	return (randstream->FRand()) * (Characters.Num());
}

*/