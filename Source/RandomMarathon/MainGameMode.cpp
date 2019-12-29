// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::SwitchLevel(FName LevelName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevel = World->GetMapName();
		if (*CurrentLevel != LevelName)
		{
			UGameplayStatics::OpenLevel(World, LevelName);
		}
	}
}