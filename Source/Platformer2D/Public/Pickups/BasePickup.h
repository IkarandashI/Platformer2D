// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class PLATFORMER2D_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	class USoundBase* PickupSound;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class UPaperFlipbookComponent* PaperFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	class UPaperSpriteComponent* PaperSprite;
};
