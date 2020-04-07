// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "RotationMatrix.h"

// Sets default values
ACharacterController::ACharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LocalPlayerState = EPlayerState::Alive;
}

// Called when the game starts or when spawned
void ACharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacterController::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterController::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("MoveForward",this,&ACharacterController::IntendMoveForward);
	PlayerInputComponent->BindAxis("MoveForward1",this,&ACharacterController::IntendMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACharacterController::IntendMoveRotate);
	PlayerInputComponent->BindAxis("MoveRight1",this,&ACharacterController::IntendMoveRotate);
}

void ACharacterController::IntendMoveForward(float Axis)
{
	if ((Controller) && (Axis != 0.0f)) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}

	//FRotator Rotation = Controller->GetControlRotation();
	//FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	//AddMovementInput(Direction, Axis);
}

void ACharacterController::IntendMoveRotate(float Axis)
{
	if ((Controller) && (Axis != 0.0f)) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}

	//FRotator Rotation = Controller->GetControlRotation();
	//FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	//FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	//AddMovementInput(Direction, Axis);
}

void ACharacterController::DestorySelf()
{

	LocalPlayerState = EPlayerState::Dead;
	//Destroy();
}

bool ACharacterController::GetPlayerState()
{
	if (LocalPlayerState == EPlayerState::Dead)
		return true;

	return false;
}
