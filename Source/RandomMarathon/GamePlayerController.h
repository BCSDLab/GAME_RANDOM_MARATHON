// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RANDOMMARATHON_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGamePlayerController();

	void ChangeCharacter(FVector NewPos);
	void Respawn();
	AGamePlayerController* GetGamePlayerController() { return this; }

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	// uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	APawn* SpawnCharacterRandomly(FVector NewPos);

	// UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// UCameraComponent* GamePlayerCamera;

private:
	FVector MovementVector;

	void AddMovementVector(FVector Vector) { MovementVector += Vector; };

	void ConsumeMovementVector()
	{
		if (!MovementVector.IsNearlyZero())
		{
			if (MarathonPlayerPawn)
			{
				if (MovementVector.Size() > 1.0f) 
				{
					MovementVector.Normalize();
				}

				MarathonPlayerPawn->AddMovementInput(MovementVector * PlayerCurrentSpeedRate);
			}
			MovementVector = FVector(0, 0, 0);
		}
	}

	float PlayerCurrentSpeedRate;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameHUDAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	class UUserWidget* GameHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Joystick")
	class UTouchInterface* LeftJoystick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TArray<TSubclassOf<class ABaseCharacter>> Characters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	APawn* MarathonPlayerPawn;

	UFUNCTION(BlueprintCallable, Category = "PlayerAction")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "PlayerAction")
	void Skill();

protected:
	class AGameGameMode* MarathonGameMode;
};
