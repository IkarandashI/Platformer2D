// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/CoinPickup.h"

#include "PlayerCharacter/PlayerPaperZDCharacter.h"
#include "UI/PlayerHUD.h"

void ACoinPickup::PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: SaveGame
	Super::PickUp(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(OtherActor);
	if (Player)
	{
		if (Player->GetCoins() > 99.f)
		{
			Player->SetCoins(0.f);
			Player->SetLives(Player->GetLives() + 1.f);
			Player->PlayerHUDref->UpdateLives();
			Player->PlayerHUDref->UpdateCoins();
		}
		else
		{
			Player->SetCoins(Player->GetCoins() + CoinsToAdd);
			Player->PlayerHUDref->UpdateCoins();
		}
		Destroy();
	}
}
