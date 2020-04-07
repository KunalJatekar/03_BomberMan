// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bomb.generated.h"

UCLASS()
class G03_BOMBERMAN_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float SpawnDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 BompCount = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UParticleSystemComponent* ExplosionBlast = nullptr;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchBomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	void OnTimerExpire();

	void SpawnExplosion();

	void CheckHit(FVector SweepStart, FVector SweepEnd);
};
