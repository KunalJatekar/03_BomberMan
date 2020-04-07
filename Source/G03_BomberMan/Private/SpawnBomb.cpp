// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBomb.h"
#include "Bomb.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
USpawnBomb::USpawnBomb()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnBomb::BeginPlay()
{
	Super::BeginPlay();

	bombCount = 1;
	canSpawn = true;
}


// Called every frame
void USpawnBomb::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpawnBomb::Fire()
{
	if (!ensure(BombBlueprint)) { return; }

	// Spawn a bomb at a player location
	auto Bomb = GetWorld()->SpawnActor<ABomb>(BombBlueprint, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());

	Bomb->LaunchBomb();
	canSpawn = false;

	bombCount--;
}

