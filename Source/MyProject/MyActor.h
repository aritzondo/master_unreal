// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FMyActorOverlapDelegate, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);

UCLASS()
class MYPROJECT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integers")
	int MaxHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integers")
	int CurrentHealth = 100;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integers")
	int HealthRegenPerSecond = 10;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Integers")
	int DamagePerHit = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hierarchy")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hierarchy")
	UStaticMeshComponent* StaticMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float Add(float a, float b);
	float Substract(float  a, float b);
	float Multiply(float  a, float b);
	float Divide(float  a, float b);
	UFUNCTION()
	void ActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FMyActorOverlapDelegate ActorDelegate;
};
