// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BasePickup.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComponent);

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("PaperFlipbook");
	PaperFlipbook->SetupAttachment(GetRootComponent());

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>("PaperSprite");
	PaperSprite->SetupAttachment(GetRootComponent());
	
}

void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::PickUp);
}

void ABasePickup::PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (PickupSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}
}
