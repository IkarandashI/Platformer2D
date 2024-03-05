// Fill out your copyright notice in the Description page of Project Settings.


#include "Traps/MovingSaw.h"

#include "PaperFlipbookComponent.h"
#include "PaperZDCharacter.h"
#include "Components/InterpToMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMovingSaw::AMovingSaw()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);

	PaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("PaperFlipbook");
	PaperFlipbook->SetupAttachment(GetRootComponent());

	InterpToMovement = CreateDefaultSubobject<UInterpToMovementComponent>("InterpToMovement");
}

void AMovingSaw::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMovingSaw::OverlapActor);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMovingSaw::EndOverlapActor);

	InterpToMovement->Duration = Speed;
}

void AMovingSaw::OverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APaperZDCharacter* Player = Cast<APaperZDCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (OtherActor != nullptr && OtherActor == Player  && DamageOnce == true)
	{
		TSubclassOf<class UDamageType> DamageTypeClass;
		AController* EventInstigater = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		UGameplayStatics::ApplyDamage(OtherActor, 1.f, EventInstigater, this, DamageTypeClass);
		DamageOnce= false;

		FVector From = OtherActor->GetActorLocation();
		FVector To = GetActorLocation();
		float VectorFloat;
	
		UKismetMathLibrary::GetDirectionUnitVector(From, To).X < 0.f ? VectorFloat = -1.f : VectorFloat = 1.f;
		Player->LaunchCharacter(FVector(VectorFloat * -2000, 0.f, 150.f), false, false);
	}
}

void AMovingSaw::EndOverlapActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	DamageOnce = true;
}

