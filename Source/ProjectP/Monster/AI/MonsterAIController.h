// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonsterAIController();
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> aiPerception;

	UAISenseConfig_Sight* sightConfig;

	UBehaviorTree* aiTree;

	AActor* target = nullptr;

	float lookAroundAccTime = 0.f;
	float lookAroundTime = 3.f;

	float attackAccTime = 0.f;
	float attackDelay = 1.f;


	float rangedCoolTime = 0.f;
	float rangedCoolTimeMax = 1.5f;

protected: 
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	virtual void OnConstruction(const FTransform& Transform);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
public:

	UFUNCTION()
	void OnTargetUpdate(AActor* actor, FAIStimulus AIStuimulus);
	UFUNCTION()
	void OnUpdate(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void OnTargetForgotten(AActor* actor);
	UFUNCTION()
	void OnTargetInfoUpdate(const FActorPerceptionUpdateInfo& UpdateInfo);

public:
	void PlayerDead();

protected:
	virtual void Attack();
	virtual void Ranged();
	virtual void LookAround(float DeltaTime);
	virtual bool Patrol();
	virtual void UpdateCapsule();
	virtual void Pattern(float DeltaTime);

public:
	AActor* GetTarget() { return target; }
	void SetSightRadius(float Radius);

	bool IsTargetAttackDistance();
};
