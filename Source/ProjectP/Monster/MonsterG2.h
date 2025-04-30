// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "../Player/Equipment/EquipmentItem.h"
#include "../player/Equipment/WeaponComponent.h"
#include "MonsterG2.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AMonsterG2 : public AMonster
{
	GENERATED_BODY()
public:
	AMonsterG2();
protected:

	TObjectPtr<UEquipmentItem> equipItem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual void Attack();
	virtual void NormalAttack();
	virtual void NormalStaggerAttack();
	virtual void FrontDodgeThrust();

	virtual void FrontDodge();
	virtual void Thrust();
	virtual void AttackPattern();
};
