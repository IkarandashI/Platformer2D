// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<class UPlayerHeart> PlayerHeartClass;

	TArray<class UPlayerHeart*> PlayerHeartref;
	TArray<class UPlayerHeart*> LostPlayerHeartref;

	void InitializeHeart();
	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	class UWrapBox* Hearts_Box;

	UPROPERTY(meta=(BindWidget))
	class UImage* Apples_Image;

	UPROPERTY(meta=(BindWidget))
	class UImage* Coins_Image;

	UPROPERTY(meta=(BindWidget))
	class UImage* Lives_Image;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Apples_Text;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* MaxApples_Text;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Coins_Text;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* Lives_Text;

	float NumofHearts = 0.f;

public:
	void DamagePlayer(float Damage);
	void HealPlayer(float Heal);
	void UpdateApples();
	void UpdateLives();
	void UpdateCoins();
};
