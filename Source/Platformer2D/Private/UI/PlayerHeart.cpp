// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHeart.h"

#include "Components/Image.h"

void UPlayerHeart::RemoveHeart()
{
	Heartfull_Image->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHeart::AddHeart()
{
	Heartfull_Image->SetVisibility(ESlateVisibility::Visible);
}
