// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyHealthBar.h"

#include "ActorComponent/AttributeComponent.h"
#include "Components/ProgressBar.h"
#include "Enemy/EnemyPaperZDCharacter.h"

void UEnemyHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthPercent();
}

void UEnemyHealthBar::SetHealthPercent()
{
	if (Enemyref == nullptr) return;

	UAttributeComponent* AttributeComponent = Cast<UAttributeComponent>(Enemyref->GetComponentByClass(UAttributeComponent::StaticClass()));
	if (IsValid(AttributeComponent))
	{
		float EnemyHealth = AttributeComponent->GetHealth();
		float EnemyMaxHealth = AttributeComponent->GetMaxHealth();
	
		HealthBar->SetPercent(EnemyHealth/EnemyMaxHealth);
	}
}
