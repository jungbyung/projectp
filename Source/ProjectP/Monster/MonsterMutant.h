// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "Monster.h"
#include "MonsterMutant.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AMonsterMutant : public AMonster
{
	GENERATED_BODY()
	
public:
	AMonsterMutant();

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
	virtual void NormalAttack();

};
