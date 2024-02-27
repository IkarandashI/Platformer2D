// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Platform/BasePlatform.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER2D_API AMovingPlatform : public ABasePlatform
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (MakeEditWidget = true))
	FVector Location1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (MakeEditWidget = true))
	FVector Location2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Speed;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UInterpToMovementComponent* InterpToMovement;
};
