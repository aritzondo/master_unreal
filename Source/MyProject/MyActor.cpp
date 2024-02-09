// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include <string>

// Sets default values
AMyActor::AMyActor() : MaxHealth(100), CurrentHealth(100), HealthRegenPerSecond(10), DamagePerHit(10), CapsuleComponent(nullptr), StaticMeshComponent(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(50, 100);
	SetRootComponent(CapsuleComponent);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(CapsuleComponent);

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Calling Add(2,3), result: %f"), this->Add(2,3));
	UE_LOG(LogTemp, Warning, TEXT("Calling Substract(2,3), result: %f"), this->Substract(2, 3));
	UE_LOG(LogTemp, Warning, TEXT("Calling Multiply(2,3), result: %f"), this->Multiply(2, 3));
	UE_LOG(LogTemp, Warning, TEXT("Calling Divide(2,3), result: %f"), this->Divide(2, 3));

	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::ActorOverlap);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth < MaxHealth) {
		CurrentHealth += HealthRegenPerSecond * DeltaTime;
	}
}

float AMyActor::Add(float  a, float b)
{
	return a + b;
}

float AMyActor::Substract(float  a, float b)
{
	return a - b;
}

float AMyActor::Multiply(float  a, float b)
{
	return a * b;
}

float AMyActor::Divide(float  a, float b)
{
	return a / b;
}

void AMyActor::ActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("ActorOverlap = %s"), *OtherActor->GetName());

	ActorDelegate.Broadcast(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

