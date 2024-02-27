// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "ApplePickup.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API AApplePickup : public ABasePickup
{
	GENERATED_BODY()

	virtual void PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	int ApplesToAdd;
};
