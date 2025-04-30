// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MonsterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UMonsterMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:
	UMonsterMovementComponent();

protected:

	float gravity = 980.f;

	FVector velocity;

	float maxSpeed;



	float dodgeAccTime = 3.f;
	float dodgeCoolTime = 3.f;
	float dodgeDistance = 2.2f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	void SetMaxSpeed(float MaxSpeed) { maxSpeed = MaxSpeed; }

	bool DodgeReady() { return dodgeAccTime >= dodgeCoolTime; }

	void DodgeInit() { dodgeAccTime = 0.f; }

};
