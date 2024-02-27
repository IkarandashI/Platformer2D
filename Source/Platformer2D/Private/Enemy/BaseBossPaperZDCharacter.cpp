// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseBossPaperZDCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PaperZDAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/BossHealthBar.h"


ABaseBossPaperZDCharacter::ABaseBossPaperZDCharacter()
{
	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("AttributeComponent");
}

void ABaseBossPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	float InRate = UKismetMathLibrary::RandomFloatInRange(2.f, 4.f);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ABaseBossPaperZDCharacter::Attack, InRate, true);

	CreateBossHealthBar();
	BossHealthBarref->Bossref = this;
	
	OnTakeAnyDamage.AddDynamic(this, &ABaseBossPaperZDCharacter::OnTakeHit);
}

void ABaseBossPaperZDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsDead)
	{
		HandleRotation();
		HandleMovement();
	}
}

void ABaseBossPaperZDCharacter::HandleRotation()
{
	FVector From = GetActorLocation();
	FVector To = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
	float DirectionIndex = (To - From).GetSafeNormal().X;

	if (DirectionIndex > 0.f)
	{
		SetActorRotation(FRotator(0.f));
	}
	else
	{
		SetActorRotation(FRotator(0.f, 180.f, 0.f));
	}
}

void ABaseBossPaperZDCharacter::HandleMovement()
{
	FVector BossLocation = GetActorLocation();
	FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
	FVector Distance = PlayerLocation - BossLocation;

	float MovementDirection = Distance.GetSafeNormal().X;
	
	if (abs(Distance.X) > BossMeleeAttackRange)
	{
		AddMovementInput(FVector(1.f, 0.f, 0.f), MovementDirection * 10.f);
	}
}

void ABaseBossPaperZDCharacter::Attack()
{
	if (bIsDamaged || bIsDead) return;

	GetAnimInstance()->JumpToNode(AttackAnimName);
}

void ABaseBossPaperZDCharacter::OnTakeHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	BossHealthBarref->SetHealthPercent();
	FVector From = DamageCauser->GetActorLocation();
	FVector To = GetActorLocation();
	float VectorFloat;
		
	UKismetMathLibrary::GetDirectionUnitVector(From, To).X < 0.f ? VectorFloat = 1.f : VectorFloat = -1.f;
	LaunchCharacter(FVector(VectorFloat * -1200, 0.f, 300.f), false, false);
	GetWorldTimerManager().SetTimer(SetMovementModeFlyTimer, this, &ABaseBossPaperZDCharacter::SetMovementModeFly, 0.5f);
	if (AttributeComponent->GetHealth() <= 0.f)
	{
		Die();
	}
	else
	{
		TakeHit();
	}
}

void ABaseBossPaperZDCharacter::CreateBossHealthBar()
{
	if (IsValid(BossHealthBarClass))
	{
		BossHealthBarref = Cast<UBossHealthBar>(CreateWidget(GetWorld(), BossHealthBarClass));
		if (BossHealthBarref != nullptr)
		{
			BossHealthBarref->AddToViewport();
		}
	}
}

void ABaseBossPaperZDCharacter::TakeHit()
{
	GetAnimInstance()->JumpToNode(TakeHitAnimName);
	
	if(GetWorldTimerManager().IsTimerActive(IsDamagedTimer))
	{
		GetWorldTimerManager().ClearTimer(IsDamagedTimer);
	}
	GetWorldTimerManager().SetTimer(IsDamagedTimer, this, &ABaseBossPaperZDCharacter::IsDamaged, 1.f);
}

void ABaseBossPaperZDCharacter::Die()
{
	GetAnimInstance()->JumpToNode(DieAnimName);
	bIsDead = true;
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	BossHealthBarref->RemoveFromParent();
	GetWorldTimerManager().SetTimer(DieTimer, this, &ABaseBossPaperZDCharacter::DestroyEnemy, 3.f);
}

void ABaseBossPaperZDCharacter::DestroyEnemy()
{
	Destroy();
}

void ABaseBossPaperZDCharacter::IsDamaged()
{
	bIsDamaged = false;
}

void ABaseBossPaperZDCharacter::SetMovementModeFly()
{
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
}
