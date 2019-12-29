// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class RANDOMMARATHON_API APortal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Empty Object")
	class UStaticMeshComponent* EmptyObject;

	UPROPERTY(VisibleAnywhere, Category = "Portal Enter")
	class UBoxComponent* PortalEnter;
	
	UPROPERTY(VisibleAnywhere, Category = "Portal Exit")
	class UStaticMeshComponent* PortalExit;

public:	
	// Sets default values for this actor's properties
	APortal();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
