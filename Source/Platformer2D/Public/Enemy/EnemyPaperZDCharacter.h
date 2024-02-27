// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "EnemyPaperZDCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API AEnemyPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

protected:
	AEnemyPaperZDCharacter();
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void SetTimerToAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void ClearTimerToAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void PlayAttackAnim();
	virtual void ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	virtual void TakeHit();
	virtual void Die();
	void IsDamaged();
	void DestroyEnemy();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	
	FTimerHandle AttackTimer;
	FTimerHandle IsDamagedTimer;
	FTimerHandle DieTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SwordDamage = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float AttackTime;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName AttackAnimName = "attack";
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName TakeHitAnimName = "takehit";
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	FName DieAnimName = "death";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsDamaged = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bIsAttacking = false;

	UPROPERTY()
	class UEnemyHealthBar* HealthBarref;
	
private:
	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComponent;
	
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* WidgetComponent;
};
