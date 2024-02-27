// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API UBossHealthBar : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	class ABaseBossPaperZDCharacter* Bossref;

	UFUNCTION(BlueprintCallable)
	void SetHealthPercent();
};
