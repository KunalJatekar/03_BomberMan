// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosion.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExplosion::AExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collistion Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->OnComponentHit.AddDynamic(this, &AExplosion::OnHit);
}

// Called when the game starts or when spawned
void AExplosion::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AExplosion::OnTimerExpire, DestroyDelay, false);
}

void AExplosion::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//CollisionMesh->DestroyComponent();

	//UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	UE_LOG(LogTemp, Warning, TEXT("Actor : %s"), *Hit.GetActor()->GetName());

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AExplosion::OnTimerExpire, DestroyDelay, false);
}

void AExplosion::OnTimerExpire()
{
	Destroy();
}

