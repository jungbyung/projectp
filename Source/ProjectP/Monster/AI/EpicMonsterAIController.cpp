// Fill out your copyright notice in the Description page of Project Settings.


#include "EpicMonsterAIController.h"
#include "../Monster.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Animation/MonsterAnimInstance.h"
#include "../../UI/UIManager.h"
#include "../../UI/Main/MainWidget.h"
#include "../../Monster/MonsterStateComponent.h"
#include "../../gamemode/defaultgamestate.h"

AEpicMonsterAIController::AEpicMonsterAIController()
{
}

void AEpicMonsterAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AEpicMonsterAIController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AEpicMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEpicMonsterAIController::Attack()
{
	AMonster* Monster = GetPawn<AMonster>();
	if (IsValid(Monster))
	{

		FRotator lookAt = GetTargetRotator(GetPawn<AMonster>()->GetActorLocation(), target->GetActorLocation());
		Monster->SetActorRotation(lookAt);
		Monster->Attack();
	}
}

void AEpicMonsterAIController::LookAround(float DeltaTime)
{
	AMonster* monster = GetPawn<AMonster>();

	if (monster->GetMonsterAnimInstance()->GetAnimState() == EMonsterAnimState::Run)
	{
		monster->SetAnimState(EMonsterAnimState::Idle);
	}
	if (monster->GetMonsterAnimInstance()->GetAnimState() == EMonsterAnimState::Idle)
	{
		lookAroundAccTime += DeltaTime;

		if (lookAroundAccTime > lookAroundTime)
		{
			lookAroundAccTime = 0.f;
			monster->NextPatrolPosIndex();
		}
	}
}

bool AEpicMonsterAIController::Patrol()
{
	AMonster* monster = GetPawn<AMonster>();


	if (IsValid(monster))
	{
		if (!monster->EnablePatrolPosArray()) return false;
		EPathFollowingRequestResult::Type type = MoveToLocation(monster->GetPatrolPos());

		switch (type)
		{
		case EPathFollowingRequestResult::Failed: // 실패
			break;
		case EPathFollowingRequestResult::AlreadyAtGoal: // 도착
			return true;
			break;

		case EPathFollowingRequestResult::RequestSuccessful: // 인지
			GetPawn<AMonster>()->SetAnimState(EMonsterAnimState::Run);
			break;
		default:
			break;
		}
	}
	return false;
}

void AEpicMonsterAIController::Pattern(float DeltaTime)
{

	if (!GWorld->GetGameState<ADefaultGameState>()->IsPlayerLive())
	{
		target = nullptr;
		return;
	}
	if (target != nullptr)
	{
		AMonster* Monster = GetPawn<AMonster>();
		float AcceptanceRadius = Monster->GetMonsterState()->GetAttackDistance();

		if (Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Attack &&
			Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Death &&
			Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Skill &&
			Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Ranged)
		{
			FVector TargetLocation = target->GetActorLocation();

			EPathFollowingRequestResult::Type type = MoveToLocation(TargetLocation, AcceptanceRadius);

			DrawDebugLine(GetWorld(), Monster->GetActorLocation(), TargetLocation, FColor::Red);

			switch (type)
			{
			case EPathFollowingRequestResult::Failed: // 실패
				break;
			case EPathFollowingRequestResult::AlreadyAtGoal: // 접근
				//Attack();
				//if(Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Attack)
				attackAccTime += DeltaTime;
				if (attackAccTime > attackDelay)
				{
					attackAccTime = 0;
					Attack();

					GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("already"));
				}
				break;
			case EPathFollowingRequestResult::RequestSuccessful: // 인지
				MoveToTarget();
				break;
			}
		}
	}
}

void AEpicMonsterAIController::MoveToTarget()
{
	AMonster* Monster = GetPawn<AMonster>();
	if (Monster)
	{
		float Distance = FVector::Distance(target->GetActorLocation(), Monster->GetActorLocation());

		float monsterAttackDist = Monster->GetMonsterState()->GetAttackDistance();

		if (Distance > monsterAttackDist)
		{
			if (Monster->GetMonsterAnimInstance()->GetAnimState() != EMonsterAnimState::Dodge)
			{
				if (Monster->DodgeReady())
					Monster->FrontDodgeThrust();
				else
				{
					Monster->SetAnimState(EMonsterAnimState::Run);
				}
			}
		}

	}


}
