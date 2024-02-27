// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BaseBossPaperZDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API ABaseBossPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ABaseBossPaperZDCharacter();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void HandleRotation();
	void HandleMovement();

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float BossMeleeAttackRange = 450.f;

	void Attack();

	UFUNCTION()
	void OnTakeHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
									  AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle AttackTimer;
	FTimerHandle IsDamagedTimer;
	FTimerHandle DieTimer;
	FTimerHandle SetMovementModeFlyTimer;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName AttackAnimName = "attack";
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName TakeHitAnimName = "takehit";
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName DieAnimName = "death";

	void CreateBossHealthBar();

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UBossHealthBar> BossHealthBarClass;
	
	UPROPERTY(BlueprintReadOnly, Category="UI")
	class UBossHealthBar* BossHealthBarref;

	bool bIsDamaged;
	bool bIsDead;
	void TakeHit();
	void Die();
	void DestroyEnemy();
	void IsDamaged();
	void SetMovementModeFly();

private:
	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComponent;
};
