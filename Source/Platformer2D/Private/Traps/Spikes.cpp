// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/Spikes.h"

#include "PaperSpriteComponent.h"
#include "PaperZDCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASpikes::ASpikes()
{
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>("PaperSprite");
	PaperSprite->SetupAttachment(GetRootComponent());
}

void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ASpikes::OverlapActor);
	Box->OnComponentEndOverlap.AddDynamic(this, &ASpikes::EndOverlapActor);
}

void ASpikes::OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APaperZDCharacter* Player = Cast<APaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherActor != nullptr && OtherActor == Player && DamageOnce == true)
	{
		TSubclassOf<class UDamageType> DamageTypeClass;
		AController* EventInstigater = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UGameplayStatics::ApplyDamage(OtherActor, 1.f, EventInstigater, this, DamageTypeClass);
		DamageOnce = false;

		FVector From = OtherActor->GetActorLocation();
		FVector To = GetActorLocation();
		float VectorFloat;
	
		UKismetMathLibrary::GetDirectionUnitVector(From, To).X < 0.f ? VectorFloat = -1.f : VectorFloat = 1.f;
		Player->LaunchCharacter(FVector(VectorFloat * -1600, 0.f, 150.f), false, false);
	}
}

void ASpikes::EndOverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	DamageOnce = true;
}
