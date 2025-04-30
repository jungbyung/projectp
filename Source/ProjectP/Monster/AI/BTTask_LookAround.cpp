// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LookAround.h"
#include "../Monster.h"
#include "MonsterAIController.h"

UBTTask_LookAround::UBTTask_LookAround()
{
	NodeName = TEXT("LookAround");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_LookAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		monster->SetAnimState(EMonsterAnimState::Idle);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_LookAround::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* board = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (IsValid(board))
	{
		float acc = board->GetValueAsFloat(TEXT("LookAroundAccTime"));

		acc += DeltaSeconds;

		if (acc >= board->GetValueAsFloat(TEXT("LookAroundTime")))
		{
			acc = 0.f;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}

		board->SetValueAsFloat(TEXT("LookAroundAccTime"), acc);

	}
}

void UBTTask_LookAround::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
