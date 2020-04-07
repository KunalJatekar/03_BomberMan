// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterController.generated.h"

// Enum for Player state
UENUM()
enum class EPlayerState : uint8
{
	Alive,
	Dead
};

UCLASS(BlueprintType, Blueprintable)
class G03_BOMBERMAN_API ACharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DestorySelf();

	UFUNCTION(BlueprintPure, Category = "Setup")
	bool GetPlayerState();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EPlayerState LocalPlayerState = EPlayerState::Alive;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void IntendMoveForward(float Throw);

	void IntendMoveRotate(float Throw);
};
