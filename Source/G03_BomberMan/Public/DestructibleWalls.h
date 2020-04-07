// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleWalls.generated.h"

UCLASS()
class G03_BOMBERMAN_API ADestructibleWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleWalls();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DestorySelf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
