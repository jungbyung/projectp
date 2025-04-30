// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStateComponent.h"

UDataTable* UMonsterStateComponent::stateData = nullptr;

// Sets default values for this component's properties
UMonsterStateComponent::UMonsterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	if (!stateData)
	{
		const ConstructorHelpers::FObjectFinder<UDataTable>
			monsterState(TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_MonsterState.DT_MonsterState'"));

		if (monsterState.Succeeded())
			stateData = monsterState.Object;
	}
}


// Called when the game starts
void UMonsterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	if (stateData)
	{
		FMonsterStateData* MonsterState = stateData->FindRow<FMonsterStateData>(monsterRowName, "");

		if (MonsterState)
		{
			name = MonsterState->name;
			grade = MonsterState->grade;
			attackPower = MonsterState->attackPower;
			criticalHitChance = MonsterState->criticalHitChance;
			criticalHitRate = MonsterState->criticalHitRate;
			attackDistance = MonsterState->attackDistance;
			attackSpeed = MonsterState->attackSpeed;
			walkSpeed = MonsterState->walkSpeed;
			runSpeed = MonsterState->runSpeed;
			hp = MonsterState->hp;
			hpMax = MonsterState->hp;
			mp = MonsterState->mp;
			mpMax = MonsterState->mp;
			level = MonsterState->level;
			gold = MonsterState->gold;
			exp = MonsterState->exp;
			defense = MonsterState->defense;
		}
	}
}


// Called every frame
void UMonsterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

