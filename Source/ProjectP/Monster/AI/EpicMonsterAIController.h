// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterAIController.h"
#include "EpicMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AEpicMonsterAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AEpicMonsterAIController();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Attack();
	virtual void LookAround(float DeltaTime);
	virtual bool Patrol();
	virtual void Pattern(float DeltaTime);

	void MoveToTarget();

};
