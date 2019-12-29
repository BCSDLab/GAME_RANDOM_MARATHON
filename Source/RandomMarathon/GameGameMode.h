// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMARATHON_API AGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameGameMode();

	void CountLanes(int Number);
	APawn* SpawnMarathonCharacter(int Order, FVector NewPos);
	int SelectCharacterRandomly();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<class ABaseCharacter>> Characters;

protected:
	void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Control")
	int TargetNumberLanes;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Control")
	int CurrentNumberLanes;
};
