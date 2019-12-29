// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceNull.h"

#include "GameGameMode.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AGamePlayerController::AGamePlayerController()
{
	/*
	GamePlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GamePlayerCamera"));
	GamePlayerCamera->SetupAttachment(GetRootComponent());
	GamePlayerCamera->bUsePawnControlRotation = false;
	GamePlayerCamera->bConstrainAspectRatio = true;
	GamePlayerCamera->bLockToHmd = true;
	GamePlayerCamera->AspectRatio = 1080/1920;
	*/
}

void AGamePlayerController::ChangeCharacter(FVector NewPos)
{
	UnPossess();
	MarathonGameMode->CountLanes(1);
	MarathonPlayerPawn->Destroy();
	MarathonPlayerPawn = SpawnCharacterRandomly(NewPos);
	Possess(MarathonPlayerPawn);
}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// GamePlayerCamera->SetWorldLocation(GetPawn()->GetActorLocation() + FVector(-500, 0, 600));
	// GamePlayerCamera->SetWorldRotation(FRotator(0.f, -50.f, 0.f));
	MarathonPlayerPawn = GetPawn();
	if (MarathonPlayerPawn)
	{
		UCharacterMovementComponent * MovementComponent = Cast<ACharacter>(MarathonPlayerPawn)->GetCharacterMovement();
		PlayerCurrentSpeedRate = Cast<ABaseCharacter>(MarathonPlayerPawn)->GetCurrentSpeedRate();
		if (MovementComponent->MaxWalkSpeed == 600) {
			MovementComponent->MaxWalkSpeed *= PlayerCurrentSpeedRate;
		}
		UE_LOG(LogTemp, Log, TEXT("MaxWalkSpeed : %f"), MovementComponent->MaxWalkSpeed);
	}
	ConsumeMovementVector();
}

void AGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AGamePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGamePlayerController::MoveRight);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GameHUDAsset)
	{
		GameHUD = CreateWidget<UUserWidget>(this, GameHUDAsset);
		GameHUD->AddToViewport();
		GameHUD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (LeftJoystick)
	{
		ActivateTouchInterface(LeftJoystick);
	}

	MarathonGameMode = Cast<AGameGameMode>(GetWorld()->GetAuthGameMode());

}

void AGamePlayerController::MoveForward(float Value)
{
	FString fst = FString::SanitizeFloat(Value);
	// UE_LOG(LogTemp, Log, TEXT("%s"), *fst);
	if (Value != 0)
	{
		AddMovementVector(FVector(1, 0, 0) * Value);
	}
}

void AGamePlayerController::MoveRight(float Value)
{
	if (Value != 0)
	{
		AddMovementVector(FVector(0, 1, 0) * Value);
	}
}

APawn* AGamePlayerController::SpawnCharacterRandomly(FVector NewPos)
{
	// 난수 생성
	static FRandomStream* randstream = new FRandomStream();
	randstream->FRandRange(0.0, 1.0f);

	ABaseCharacter* RetPawn;

	RetPawn = GetWorld()->SpawnActor<ABaseCharacter>(Characters[(randstream->FRand()) * (Characters.Num())], NewPos, FRotator::ZeroRotator);
	RetPawn->SetLastSpawnPos(NewPos);
	return RetPawn;
}

void AGamePlayerController::Respawn() 
{
	UnPossess();
	APawn* NewPawn = SpawnCharacterRandomly(((ABaseCharacter*)MarathonPlayerPawn)->GetLastSpawnPos());
	MarathonPlayerPawn->Destroy();
	Possess(NewPawn);
}

void AGamePlayerController::Attack()
{
	UE_LOG(LogTemp, Log, TEXT("PlayerController Attack()"));
	
}

void AGamePlayerController::Skill()
{
	UE_LOG(LogTemp, Log, TEXT("PlayerController Skill()"));
	
}