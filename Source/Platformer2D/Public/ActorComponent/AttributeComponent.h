// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER2D_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();

	float GetHealth() { return Health; }
	float GetMaxHealth() { return MaxHealth; }
	
	void SetHealth(float NewHealth) { Health = NewHealth; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Attribute", meta=(AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Attribute")
	float MaxHealth;

	UFUNCTION()
	void ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
};
