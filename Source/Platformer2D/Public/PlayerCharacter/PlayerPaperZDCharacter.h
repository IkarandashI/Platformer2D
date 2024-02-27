// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "InputActionValue.h"
#include "PlayerPaperZDCharacter.generated.h"

UCLASS()
class PLATFORMER2D_API APlayerPaperZDCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* RangeAttackAction;

public:
	APlayerPaperZDCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetPlayerRotation();

	float GetApples() { return Apples; }
	float GetMaxApples() { return MaxApples; }
	float GetLives() { return Lives; }
	float GetCoins() { return Coins; }

	void SetApples(int NewApples) { Apples = NewApples; }
	void SetCoins(float NewCoins) { Coins = NewCoins; }
	void SetLives(float NewLives) { Lives = NewLives; }
	

	UPROPERTY(BlueprintReadOnly, Category="UI")
	class UPlayerHUD* PlayerHUDref;

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
	void SetEnchancedInput();
	void SetInputGameMode();
	void CreatePlayerHUD();

	void OnPressedJump();
	
	void Move(const FInputActionValue& Value);
	void bMoveRight(float RightVectorFloat);
	bool MoveRight = true;
	
	void Dash();
	
	
	UFUNCTION(BlueprintCallable)
	void Respawn();

	UFUNCTION()
	void GrabOnWall(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	void DownFromWall();

	UFUNCTION(BlueprintCallable)
	void PlayerAttack();
	void Attack();
	void RangeAttack();
	void ResetRangeAttack();
	void Die();
	bool CanRangeAttack = true;
	
	FTimerHandle DashTimer;
	FTimerHandle RangeAttackTimer;
	FTimerHandle OnWallTimer;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float RangeAttackCooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float SwordDamage = 1.f;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<AActor> ProjectileClass;

	UFUNCTION()
	void TakeHit(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );

	UPROPERTY(EditDefaultsOnly, Category="TakeHit")
	TSubclassOf<UCameraShakeBase> TakeHitCameraShake;

	UPROPERTY(EditDefaultsOnly, Category="TakeHit")
	FName DeathAnimName;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UPlayerHUD> PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> GameOverWidget;

	UPROPERTY(BlueprintReadWrite)
	bool CanDash = true;

	UPROPERTY(BlueprintReadWrite)
	bool CanAttack = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite) 
	float DashInAir = 1.f;

	UPROPERTY(EditDefaultsOnly, Category= "Animations")
	FName DashAnimation = "dash";

	UPROPERTY(EditDefaultsOnly, Category= "Animations")
	FName AttackAnimation = "attack";

	UPROPERTY(EditDefaultsOnly, Category= "Animations")
	FName OnWallAnimation = "onwall";

	UPROPERTY(BlueprintReadWrite)
	bool IsWallSlide;
	
	UPROPERTY(EditDefaultsOnly, Category="Dash")
	float CanDashTime = 0.3f;

	UPROPERTY(BlueprintReadOnly)
	bool CanRespawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
	float Lives = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
	int Apples = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
	int MaxApples = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game")
	float Coins = 3.f;

	UPROPERTY(BlueprintReadWrite)
	FVector Checpoint;

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta=(AllowPrivateAccess = "true"))
	float StartingGravityScale;

	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComponent;
};
