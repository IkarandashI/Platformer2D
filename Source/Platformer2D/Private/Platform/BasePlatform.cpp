// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform/BasePlatform.h"

#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ABasePlatform::ABasePlatform()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	SetRootComponent(Box);

	PaperSprite = CreateDefaultSubobject<UPaperSpriteComponent>("PaperSprite");
	PaperSprite->SetupAttachment(GetRootComponent());
}

void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();

	PaperSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Box->OnComponentBeginOverlap.AddDynamic(this, &ABasePlatform::OverlapActor);
	Box->OnComponentEndOverlap.AddDynamic(this, &ABasePlatform::HidePlatform);
}

void ABasePlatform::OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter == Player)
	{
		GetWorldTimerManager().SetTimer(ShowPlatformTimer, this, &ABasePlatform::ShowPlatform, 0.2f);
	}
}

void ABasePlatform::ShowPlatform()
{
	PaperSprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABasePlatform::HidePlatform(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter == Player)
	{
		PaperSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
