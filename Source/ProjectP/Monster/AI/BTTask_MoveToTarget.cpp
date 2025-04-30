// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToTarget.h"
#include "../Monster.h"
#include "../MonsterSpawner.h"
#include "MonsterAIController.h"

UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("MoveToTarget");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		monster->SetAnimState(EMonsterAnimState::Run);
	}

	UBlackboardComponent* blackBoard = OwnerComp.GetAIOwner()->GetBlackboardComponent();

	if (IsValid(blackBoard))
	{
		AcceptableRadius = blackBoard->GetValueAsFloat(TEXT("AttackDistance"));

	}
	return result;
}

void UBTTask_MoveToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	FVector srcLocation, destLocation;
	float AttackDist = 0.f;

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		srcLocation = monster->GetActorLocation();
		UCapsuleComponent* capsule = monster->GetCapsule();

		monster->SetAnimState(EMonsterAnimState::Run);
		if (IsValid(capsule))
		{
			srcLocation.Z -= capsule->GetScaledCapsuleHalfHeight();
			UBlackboardComponent* board = OwnerComp.GetAIOwner()->GetBlackboardComponent();

			if (IsValid(board))
			{

				AttackDist = board->GetValueAsFloat(TEXT("AttackDistance"));
				
				AActor* actor = Cast<AActor>(board->GetValueAsObject(TEXT("Target")));
				if (IsValid(actor))
				{
					destLocation = actor->GetActorLocation();
					capsule = Cast<UCapsuleComponent>(actor->GetRootComponent());

					if (IsValid(capsule))
						destLocation.Z -= capsule->GetScaledCapsuleHalfHeight();
				}
			}
		}
	}

	float dist = FVector::Dist(srcLocation, destLocation);

	if (dist <= AttackDist)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);



}

void UBTTask_MoveToTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	OwnerComp.GetAIOwner()->StopMovement();

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
		monster->SetAnimState(EMonsterAnimState::Idle);
}
