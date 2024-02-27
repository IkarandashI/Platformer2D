// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PlayerPaperZDCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimInstance.h"
#include "ActorComponent/AttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PlayerHUD.h"


APlayerPaperZDCharacter::APlayerPaperZDCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>("AttributeComponent");

	DeathAnimName = "death";
}

void APlayerPaperZDCharacter::BeginPlay()
{
	Super::BeginPlay();

	Checpoint = GetActorLocation();
	StartingGravityScale = GetCharacterMovement()->GravityScale;
	
	SetInputGameMode();
	SetEnchancedInput();
	CreatePlayerHUD();

	OnTakeAnyDamage.AddDynamic(this, &APlayerPaperZDCharacter::TakeHit);
	OnActorHit.AddDynamic(this, &APlayerPaperZDCharacter::GrabOnWall);
}


void APlayerPaperZDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerPaperZDCharacter::Move);
		
		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerPaperZDCharacter::OnPressedJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerPaperZDCharacter::Dash);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &APlayerPaperZDCharacter::Attack);

		// RangeAttack
		EnhancedInputComponent->BindAction(RangeAttackAction, ETriggerEvent::Started, this, &APlayerPaperZDCharacter::RangeAttack);
	}
}

void APlayerPaperZDCharacter::SetPlayerRotation()
{
	FRotator PlayerRotation(0.f);
	if (GetCharacterMovement()->Velocity.X > 0.f)
	{
		PlayerRotation = FRotator(0.f);
		
	}
	else if (GetCharacterMovement()->Velocity.X < 0.f)
	{
		PlayerRotation = FRotator(0.f, 180.f, 0.f);
	}
	else
	{
		if (MoveRight == true)
		{
			PlayerRotation = FRotator(0.f);
		}
		else
		{
			PlayerRotation = FRotator(0.f, 180.f, 0.f);
		}
	}

	Controller->SetControlRotation(PlayerRotation);
}

void APlayerPaperZDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


	if (Controller != nullptr || !IsWallSlide)
	{
		SetPlayerRotation();
	}
	
}

void APlayerPaperZDCharacter::SetEnchancedInput()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerPaperZDCharacter::SetInputGameMode()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
}

void APlayerPaperZDCharacter::CreatePlayerHUD()
{
	if (IsValid(PlayerHUDClass))
	{
		PlayerHUDref = Cast<UPlayerHUD>(CreateWidget(GetWorld(), PlayerHUDClass));
		if (PlayerHUDref != nullptr)
		{
			PlayerHUDref->AddToViewport();
		}
	}
}

void APlayerPaperZDCharacter::OnPressedJump()
{
	if (IsWallSlide == false)
	{
		Jump();
	}
	else
	{
		float XLaunchFloat = GetActorForwardVector().X * -1000.f;
		LaunchCharacter(FVector(XLaunchFloat, 0.f, 750.f), true, true);
	}
	
}

void APlayerPaperZDCharacter::Move(const FInputActionValue& Value)
{
	float Movementfloat = Value.Get<float>();
	if (Controller != nullptr)
	{
		bMoveRight(Movementfloat);
		AddMovementInput(FVector(1.f,0.f,0.f), Movementfloat);
	}
}

void APlayerPaperZDCharacter::bMoveRight(float RightVectorFloat)
{
	if (RightVectorFloat > 0.f)
	{
		MoveRight = true;
	}
	else if (RightVectorFloat < 0.f)
	{
		MoveRight = false;
	}
}

void APlayerPaperZDCharacter::Dash()
{
	if (!CanDash) return;
	if (GetCharacterMovement()->IsFalling() && DashInAir <= 0.f) return;
	
	FVector DashVector;
	if (MoveRight == true)
	{
		DashVector = FVector(3000.f, 0.f, 0.f);
	}
	else
	{
		DashVector = FVector(-3000.f, 0.f, 0.f);
	}
	
	if (GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->GravityScale = 0.f;
	}
	
	LaunchCharacter(DashVector, true, true);
	GetAnimInstance()->JumpToNode(DashAnimation);
	CanDash = false;
	DashInAir -= 1;
}



void APlayerPaperZDCharacter::Attack()
{
	if (!CanAttack) return;
	GetAnimInstance()->JumpToNode(AttackAnimation);
}

void APlayerPaperZDCharacter::RangeAttack()
{
	if (Apples > 0 && ProjectileClass != nullptr && CanRangeAttack)
	{
		GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorLocation() + FVector(60.f, 0.f, 30.f), GetActorRotation());
		Apples--;
		PlayerHUDref->UpdateApples();
		CanRangeAttack = false;
		GetWorldTimerManager().SetTimer(RangeAttackTimer, this, &APlayerPaperZDCharacter::ResetRangeAttack, RangeAttackCooldown);
	}
}

void APlayerPaperZDCharacter::ResetRangeAttack()
{
	GetWorldTimerManager().ClearTimer(RangeAttackTimer);
	CanRangeAttack = true;
}

void APlayerPaperZDCharacter::Die()
{
	GetAnimInstance()->JumpToNode(DeathAnimName);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(PlayerController))
	{
		DisableInput(PlayerController);
	}
	PlayerHUDref->RemoveFromParent();
}

void APlayerPaperZDCharacter::TakeHit(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                      AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	PlayerHUDref->DamagePlayer(Damage);
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), TakeHitCameraShake, GetActorLocation(), 0.f, 2000.f);
	
	if (AttributeComponent->GetHealth() <= 0.f)
	{
		Die();
	}
	CanAttack = true;
}

void APlayerPaperZDCharacter::Respawn()
{
	if (Lives > 0.f)
	{
		EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		AttributeComponent->SetHealth(AttributeComponent->GetMaxHealth());
		SetActorLocation(Checpoint);
		Lives -= 1.f;
		CanRespawn = true;
		CreatePlayerHUD();
	}
	else
	{
		CanRespawn = false;
		if (IsValid(GameOverWidget))
		{
			UUserWidget* GameOver = CreateWidget(GetWorld(), GameOverWidget);
			if (GameOver != nullptr)
			{
				GameOver->AddToViewport();
			}
		}
	}
}

void APlayerPaperZDCharacter::GrabOnWall(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
	const FHitResult& Hit)
{
	FVector Start = GetActorLocation();
	FVector End = GetActorForwardVector() * FVector(100.f, 0.f, 0.f) + Start;

	TArray<AActor*> ActorsToIgnore;

	FHitResult HitResult;
	
	bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

	if (bHit && HitResult.GetActor()->ActorHasTag("wall") && GetCharacterMovement()->IsFalling())
	{
		IsWallSlide = true;
		GetAnimInstance()->JumpToNode(OnWallAnimation);
		GetSprite()->SetRelativeLocation(FVector(50.f , GetSprite()->GetRelativeLocation().Y, GetSprite()->GetRelativeLocation().Z));
		if (GetWorldTimerManager().IsTimerActive(OnWallTimer))
		{
			GetWorldTimerManager().ClearTimer(OnWallTimer);
		}
		GetWorldTimerManager().SetTimer(OnWallTimer, this, &APlayerPaperZDCharacter::DownFromWall, 0.1f);
	}
}

void APlayerPaperZDCharacter::DownFromWall()
{
	IsWallSlide = false;
	GetSprite()->SetRelativeLocation(FVector(30.f , GetSprite()->GetRelativeLocation().Y, GetSprite()->GetRelativeLocation().Z));
}

void APlayerPaperZDCharacter::PlayerAttack()
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

	if (bHit)
	{
		TSubclassOf<class UDamageType> DamageTypeClass;
		UGameplayStatics::ApplyDamage(HitResult.GetActor(), SwordDamage, Controller, this, DamageTypeClass);
	}
}
