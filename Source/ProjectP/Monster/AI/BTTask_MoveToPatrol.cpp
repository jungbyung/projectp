// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToPatrol.h"
#include "../Monster.h"
#include "MonsterAIController.h"

UBTTask_MoveToPatrol::UBTTask_MoveToPatrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type type = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		monster->SetAnimState(EMonsterAnimState::Walk);
	}
	else return EBTNodeResult::Failed;

	if (!monster->EnablePatrolPosArray()) return EBTNodeResult::Failed;

	UBlackboardComponent* board = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	AcceptableRadius = 0.f;

	if (IsValid(board))
	{
		FVector pos = monster->GetPatrolPos();
		board->SetValueAsVector(TEXT("PatrolPos"), pos);
	}
	else return EBTNodeResult::Failed;

	return type;
}

void UBTTask_MoveToPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_MoveToPatrol::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		if (TaskResult == EBTNodeResult::Succeeded)
			monster->NextPatrolPosIndex();
		monster->SetAnimState(EMonsterAnimState::Idle);
	}

}
