// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD.h"

#include "ActorComponent/AttributeComponent.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "PlayerCharacter/PlayerPaperZDCharacter.h"
#include "UI/PlayerHeart.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeHeart();
	UpdateApples();
	UpdateCoins();
	UpdateLives();
}

void UPlayerHUD::InitializeHeart()
{
	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player != nullptr)
	{
		UAttributeComponent* AttributeComponent = Cast<UAttributeComponent>(Player->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (IsValid(AttributeComponent))
		{
			for (float i = 1; i <= AttributeComponent->GetHealth(); i++)
			{
				UPlayerHeart* PlayerHeartWidget = Cast<UPlayerHeart>(CreateWidget(GetWorld(), PlayerHeartClass));
				PlayerHeartref.Add(PlayerHeartWidget);
				Hearts_Box->AddChildToWrapBox(PlayerHeartWidget);
			}
		}
	}
}

void UPlayerHUD::DamagePlayer(float Damage)
{
	if (PlayerHeartref.Num() <= 0) return;
	
	for (float i = 0.f; i < Damage; i++)
	{
		UPlayerHeart* PlayerHeart = PlayerHeartref[PlayerHeartref.Num() - 1 - i];
		if (PlayerHeart != nullptr)
		{
			PlayerHeart->RemoveHeart();
			PlayerHeartref.Remove(PlayerHeart);
			LostPlayerHeartref.Add(PlayerHeart);
		}
	}
}

void UPlayerHUD::HealPlayer(float Heal)
{
	if (LostPlayerHeartref.Num() <= 0) return;
	
	for (float i = 0.f; i < Heal; i++)
	{
		UPlayerHeart* PlayerHeart = LostPlayerHeartref[LostPlayerHeartref.Num() - 1 - i];
		if (PlayerHeart != nullptr)
		{
			PlayerHeart->AddHeart();
			LostPlayerHeartref.Remove(PlayerHeart);
			PlayerHeartref.Add(PlayerHeart);
		}
	}
}

void UPlayerHUD::UpdateApples()
{
	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player != nullptr)
	{
		
		Apples_Text->SetText(UKismetTextLibrary::Conv_IntToText(Player->GetApples()));
		MaxApples_Text->SetText(UKismetTextLibrary::Conv_IntToText(Player->GetMaxApples()));
	}
}

void UPlayerHUD::UpdateLives()
{
	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player != nullptr)
	{
		Lives_Text->SetText(UKismetTextLibrary::Conv_IntToText(Player->GetLives()));
	}
}

void UPlayerHUD::UpdateCoins()
{
	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Player != nullptr)
	{
		Coins_Text->SetText(UKismetTextLibrary::Conv_IntToText(Player->GetCoins()));
	}
}
