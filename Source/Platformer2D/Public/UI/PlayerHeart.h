// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHeart.generated.h"


UCLASS()
class PLATFORMER2D_API UPlayerHeart : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	class UImage* Heartfull_Image;

	UPROPERTY(meta=(BindWidget))
	class UImage* Heartempty_Image;

public:
	void RemoveHeart();
	void AddHeart();
};
