// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "../Monster.h"
#include "monsteraicontroller.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();

	if (IsValid(monster))
	{
		monster->Attack();

	}
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonster* monster = OwnerComp.GetAIOwner()->GetPawn<AMonster>();
	FVector srcLocation, destLocation;


	if (IsValid(monster))
	{
		monster->SetAnimState(EMonsterAnimState::Attack);

		UBlackboardComponent* board = OwnerComp.GetAIOwner()->GetBlackboardComponent();

		if (IsValid(board))
		{

			if (board->GetValueAsBool(TEXT("AttackEnd")))
			{
				AActor* Target = Cast<AActor>(board->GetValueAsObject(TEXT("Target")));
				if (IsValid(Target))
				{
					FRotator lookAt = GetTargetRotator(monster->GetActorLocation(), Target->GetActorLocation());
					monster->SetActorRotation(lookAt);

					board->SetValueAsBool(TEXT("AttackEnd"), false);
				}

				srcLocation = monster->GetActorLocation();
				UCapsuleComponent* capsule = monster->GetCapsule();

				if (IsValid(capsule))
				{
					srcLocation.Z -= capsule->GetScaledCapsuleHalfHeight();
				}

				capsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

				if (IsValid(capsule))
					destLocation.Z -= capsule->GetScaledCapsuleHalfHeight();

				float AttackDist = board->GetValueAsFloat(TEXT("AttackDistance"));
				float Dist = FVector::Dist(srcLocation, destLocation);

				if (Dist > AttackDist)
					FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
				else
				{
					float AttackDelay = board->GetValueAsFloat(TEXT("AttackDelay"));
					AttackDelay += DeltaSeconds;
					float AttackDelayTime = board->GetValueAsFloat(TEXT("AttackDelayTime"));
					if (AttackDelay > AttackDelayTime)
					{
						AttackDelay = 0.f;
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					}
					board->SetValueAsFloat(TEXT("AttackDelay"), AttackDelay);
					  
				}
			}
		}
	}
}

void UBTTask_Attack::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
