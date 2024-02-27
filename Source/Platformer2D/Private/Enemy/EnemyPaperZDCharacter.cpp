// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPaperZDCharacter.h"

#include "PaperZDAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/EnemyHealthBar.h"

AEnemyPaperZDCharacter::AEnemyPaperZDCharacter()
{
	Tags.Add(FName("enemy"));

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("AttributeComponent");

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(GetRootComponent());

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(GetRootComponent());
}

void AEnemyPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthBarref = Cast<UEnemyHealthBar>(WidgetComponent->GetWidget());
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyPaperZDCharacter::SetTimerToAttack);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AEnemyPaperZDCharacter::ClearTimerToAttack);

	HealthBarref->Enemyref = this;
}

void AEnemyPaperZDCharacter::SetTimerToAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player == OtherActor)
	{
		bIsAttacking = true;
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyPaperZDCharacter::PlayAttackAnim, AttackTime, true);
	}
}

void AEnemyPaperZDCharacter::ClearTimerToAttack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsAttacking = false;
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void AEnemyPaperZDCharacter::PlayAttackAnim()
{
	if (bIsDead) return;
	GetAnimInstance()->JumpToNode(AttackAnimName);
}

void AEnemyPaperZDCharacter::ApplyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	bIsDamaged = true;
	HealthBarref->SetHealthPercent();

	if (AttributeComponent->GetHealth() <= 0.f)
	{
		Die();
	}
	else
	{
		TakeHit();
	}
}

void AEnemyPaperZDCharacter::TakeHit()
{
	GetAnimInstance()->JumpToNode(TakeHitAnimName);
	WidgetComponent->SetVisibility(true);

	if(GetWorldTimerManager().IsTimerActive(IsDamagedTimer))
	{
		GetWorldTimerManager().ClearTimer(IsDamagedTimer);
	}
	GetWorldTimerManager().SetTimer(IsDamagedTimer, this, &AEnemyPaperZDCharacter::IsDamaged, 1.f);
}

void AEnemyPaperZDCharacter::Attack()
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * FVector(150.f, 0.f,0.f) + Start;
    	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
    
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
    
	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, ObjectTypes, false, ActorsToIgnore,
		EDrawDebugTrace::None, HitResult, true);
    
	if (bHit && HitResult.GetActor() == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		TSubclassOf<class UDamageType> DamageTypeClass;
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), SwordDamage, Controller, this, DamageTypeClass);
	}
}

void AEnemyPaperZDCharacter::Die()
{
	GetAnimInstance()->JumpToNode(DieAnimName);
	WidgetComponent->SetVisibility(false);
	bIsDead = true;
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	GetWorldTimerManager().SetTimer(DieTimer, this, &AEnemyPaperZDCharacter::DestroyEnemy, 3.f);
}

void AEnemyPaperZDCharacter::IsDamaged()
{
	bIsDamaged = false;
}

void AEnemyPaperZDCharacter::DestroyEnemy()
{
	Destroy();
}
