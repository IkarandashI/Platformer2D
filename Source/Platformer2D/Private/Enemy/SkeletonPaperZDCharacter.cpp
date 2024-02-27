// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SkeletonPaperZDCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


ASkeletonPaperZDCharacter::ASkeletonPaperZDCharacter()
{
}

void ASkeletonPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnTakeAnyDamage.AddDynamic(this, &ASkeletonPaperZDCharacter::ApplyDamage);
}

void ASkeletonPaperZDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsDead)
	{
		HandleRotation();
		HandleMovement();
	}
}

void ASkeletonPaperZDCharacter::ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	Super::ApplyDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	FVector From = DamageCauser->GetActorLocation();
	FVector To = GetActorLocation();
	
	UKismetMathLibrary::GetDirectionUnitVector(From, To).X < 0.f ? VectorFloat = 1.f : VectorFloat = -1.f;
	MovementDirection = VectorFloat;
}

void ASkeletonPaperZDCharacter::TakeHit()
{
	Super::TakeHit();

	LaunchCharacter(FVector(VectorFloat * -800, 0.f, 150.f), false, false);
}

void ASkeletonPaperZDCharacter::HandleMovement()
{
	if (bIsDamaged == true ||
		GetCharacterMovement()->IsFalling() == true || bIsAttacking == true) return;
	
	AddMovementInput(FVector(1.f,0.f,0.f), MovementDirection);

	TrackWall();
	TrackFloor();
}

void ASkeletonPaperZDCharacter::HandleRotation()
{
	FRotator SkeletonRotation;
	if (MovementDirection > 0.f)
	{
		SkeletonRotation = FRotator(0.f);
	}
	else 
	{
		SkeletonRotation = FRotator(0.f, 180.f, 0.f);
	}
	SetActorRotation(SkeletonRotation);
	
}

void ASkeletonPaperZDCharacter::TrackWall()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * FVector(100.f, 0.f,0.f) + Start;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ActorsToIgnore.Add(this);

	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false, ActorsToIgnore,
		EDrawDebugTrace::None, HitResult, true);
	

	if (bHit && !GetWorldTimerManager().IsTimerActive(TurnAroundTimer))
	{
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		GetWorldTimerManager().SetTimer(TurnAroundTimer, this, &ASkeletonPaperZDCharacter::TurnAround, TurnAroundTime);
	}
}

void ASkeletonPaperZDCharacter::TrackFloor()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * FVector(100.f, 0.f,0.f) + (Start - FVector(0.f, 0.f, 100.f));
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	ActorsToIgnore.Add(this);


	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false, ActorsToIgnore,
		EDrawDebugTrace::None, HitResult, true);

	if (!bHit && !GetWorldTimerManager().IsTimerActive(TurnAroundTimer))
	{
		GetCharacterMovement()->MaxWalkSpeed = 0.f;
		GetWorldTimerManager().SetTimer(TurnAroundTimer, this, &ASkeletonPaperZDCharacter::TurnAround, TurnAroundTime);
	}
}

void ASkeletonPaperZDCharacter::TurnAround()
{
	GetWorldTimerManager().ClearTimer(TurnAroundTimer);
	GetCharacterMovement()->MaxWalkSpeed = EnemyMaxWalkSpeed;
	MovementDirection *= -1;
}
