// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/MovingPlatform.h"

#include "Components/InterpToMovementComponent.h"

AMovingPlatform::AMovingPlatform()
{
	InterpToMovement = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovement");
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	InterpToMovement->Duration = Speed;
}
