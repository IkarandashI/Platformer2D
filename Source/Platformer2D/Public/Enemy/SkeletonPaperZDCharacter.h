// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPaperZDCharacter.h"
#include "SkeletonPaperZDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API ASkeletonPaperZDCharacter : public AEnemyPaperZDCharacter
{
	GENERATED_BODY()

public:
	ASkeletonPaperZDCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) override;
	virtual void TakeHit() override;
	float VectorFloat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementDirection = -1.f;
	
	void HandleMovement();
	void HandleRotation();


	void TrackWall();
	void TrackFloor();
	void TurnAround();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxWaitTime = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnemyMaxWalkSpeed = 100.f;

	FTimerHandle TurnAroundTimer;

	UPROPERTY(EditDefaultsOnly, Category="Combot")
	float TurnAroundTime = 3.f;
};
