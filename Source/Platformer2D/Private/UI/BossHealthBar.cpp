// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BossHealthBar.h"

#include "ActorComponent/AttributeComponent.h"
#include "Components/ProgressBar.h"
#include "Enemy/BaseBossPaperZDCharacter.h"

void UBossHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	SetHealthPercent();
}

void UBossHealthBar::SetHealthPercent()
{
	if (Bossref == nullptr) return;

	UAttributeComponent* AttributeComponent = Cast<UAttributeComponent>(Bossref->GetComponentByClass(UAttributeComponent::StaticClass()));
	if (IsValid(AttributeComponent))
	{
		float BossHealth = AttributeComponent->GetHealth();
		float BossMaxHealth = AttributeComponent->GetMaxHealth();

		HealthBar->SetPercent(BossHealth/BossMaxHealth);
	}	
}
