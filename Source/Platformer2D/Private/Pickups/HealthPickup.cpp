// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPickup.h"

#include "ActorComponent/AttributeComponent.h"
#include "PlayerCharacter/PlayerPaperZDCharacter.h"
#include "UI/PlayerHUD.h"

void AHealthPickup::PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: SaveGame
	Super::PickUp(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(OtherActor);
	if (Player)
	{
		UAttributeComponent* AttributeComponent = Cast<UAttributeComponent>(Player->GetComponentByClass(UAttributeComponent::StaticClass()));
		if (IsValid(AttributeComponent))
		{
			float PlayerHealth = AttributeComponent->GetHealth();
			float PlayerMaxHealth = AttributeComponent->GetMaxHealth();
			if (PlayerHealth == PlayerMaxHealth) return;

			float NewHealth = FMath::Clamp(PlayerHealth + HealthToAdd, 0.f, PlayerMaxHealth);
			AttributeComponent->SetHealth(NewHealth);
			Player->PlayerHUDref->HealPlayer(HealthToAdd);
			Destroy();
		}
	}
}
