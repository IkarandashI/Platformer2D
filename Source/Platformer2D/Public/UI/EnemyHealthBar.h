// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthBar;

	void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	class AEnemyPaperZDCharacter* Enemyref;

	UFUNCTION(BlueprintCallable)
	void SetHealthPercent();
};
