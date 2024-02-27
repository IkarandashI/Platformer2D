// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlatform.generated.h"

UCLASS()
class PLATFORMER2D_API ABasePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePlatform();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void HidePlatform(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	FTimerHandle ShowPlatformTimer;
	void ShowPlatform();

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere)
	class UPaperSpriteComponent* PaperSprite;
};
