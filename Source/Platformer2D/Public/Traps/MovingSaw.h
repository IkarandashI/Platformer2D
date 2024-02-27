// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingSaw.generated.h"

UCLASS()
class PLATFORMER2D_API AMovingSaw : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingSaw();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (MakeEditWidget = true))
	FVector Location1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move", Meta = (MakeEditWidget = true))
	FVector Location2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Speed;
	
private:
	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* PaperFlipbook;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UInterpToMovementComponent* InterpToMovement;
};
