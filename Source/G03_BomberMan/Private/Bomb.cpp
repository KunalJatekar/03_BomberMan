// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/WeakObjectPtr.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "CharacterController.h"
#include "DestructibleWalls.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ExplosionBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Explosion Blast"));
	SetRootComponent(ExplosionBlast);
	ExplosionBlast->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::LaunchBomb()
{
	FTimerHandle TimerStart;
	GetWorld()->GetTimerManager().SetTimer(TimerStart, this, &ABomb::SpawnExplosion, SpawnDelay, false);
}

void ABomb::OnTimerExpire()
{
	Destroy();
	DestroyDelay = 2.0f;
}

void ABomb::SpawnExplosion()
{
	FVector forwardVector = GetActorLocation() + FVector(100, 0, 0);
	FVector backwardVector = GetActorLocation() + FVector(-100, 0, 0);
	FVector rightVector = GetActorLocation() + FVector(0, 100, 0);
	FVector leftVector = GetActorLocation() + FVector(0, -100, 0);

	for (int32 i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
		{
			UParticleSystemComponent * centerExplosion = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionBlast->Template, GetActorLocation(), FRotator::ZeroRotator, FVector(1, 1, 1), true, EPSCPoolMethod::None, true);
		}
			break;
		case 1:
		{
			CheckHit(GetActorLocation(), forwardVector);
		}
			break;
		case 2:
		{
			CheckHit(GetActorLocation(), backwardVector);
		}
			break;
		case 3:
		{
			CheckHit(GetActorLocation(), rightVector);
		}
			break;
		case 4:
		{
			CheckHit(GetActorLocation(), leftVector);
		}
			break;
		default:
			break;
		}
	}

	OnTimerExpire();
}

void ABomb::CheckHit(FVector SweepStart, FVector SweepEnd)
{
	// create tarray for hit results
	TArray<FHitResult> OutHits;

	// create a collision sphere
	FCollisionShape MyColSphere = FCollisionShape::MakeBox(FVector(1, 1, 1));

	// draw collision sphere
	//DrawDebugBox(GetWorld(), GetActorLocation(), MyColSphere.GetBox(), FColor::Purple, false, 1.0f, 10.0f);
	//DrawDebugBox(GetWorld(), GetActorLocation(), MyColSphere.GetSphereRadius(), 50, FColor::Purple, true);

	// check if something got hit in the sweep
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);

	if (isHit)
	{
		// loop through TArray
		for (auto& Hit : OutHits)
		{
			ACharacterController* CharacterController = Cast<ACharacterController>(Hit.Actor);
			ADestructibleWalls* DestructibleWalls = Cast<ADestructibleWalls>(Hit.Actor);

			if (CharacterController) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionBlast->Template, SweepEnd, FRotator::ZeroRotator, FVector(1, 1, 1), true, EPSCPoolMethod::None, true);
				CharacterController->DestorySelf();
				break;
			}
			if (DestructibleWalls) {
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionBlast->Template, SweepEnd, FRotator::ZeroRotator, FVector(1, 1, 1), true, EPSCPoolMethod::None, true);
				DestructibleWalls->DestorySelf();
			}
		}
	}
	else {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionBlast->Template, SweepEnd, FRotator::ZeroRotator, FVector(1, 1, 1), true, EPSCPoolMethod::None, true);
	}
}
