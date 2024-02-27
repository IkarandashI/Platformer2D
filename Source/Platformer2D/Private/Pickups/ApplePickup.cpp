// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/ApplePickup.h"
#include "PlayerCharacter/PlayerPaperZDCharacter.h"
#include "UI/PlayerHUD.h"

void AApplePickup::PickUp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Save Num of Apples in SaveGame
	Super::PickUp(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	APlayerPaperZDCharacter* Player = Cast<APlayerPaperZDCharacter>(OtherActor);
	if (Player)
	{
		int PlayerApples = Player->GetApples();
		int PlayerMaxApples = Player->GetMaxApples();
		if (PlayerApples == PlayerMaxApples) return;

		int NewApples = FMath::Clamp(PlayerApples + ApplesToAdd, 0, PlayerMaxApples);
		Player->SetApples(NewApples);

		Player->PlayerHUDref->UpdateApples();
		Destroy();
	}
}
