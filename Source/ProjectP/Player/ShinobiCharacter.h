// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "ShinobiCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AShinobiCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AShinobiCharacter();
protected:
	bool isRightHand = true;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual void NormalAttack();
	virtual void SetRightWeapon();
	virtual void SetLeftWeapon();
	virtual void SkillAttack();

	virtual void Hit();
	virtual void HitDir(const FVector& HitLocation);
};
