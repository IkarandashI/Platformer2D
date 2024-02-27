// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BaseSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API UBaseSaveGame : public USaveGame
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadWrite)
	float Lives;

	UPROPERTY(BlueprintReadWrite)
	float Coins;

	UPROPERTY(BlueprintReadWrite)
	int Apples;

	UPROPERTY(BlueprintReadWrite)
	TArray<bool> Levels;
};
