// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "../Monster.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Animation/MonsterAnimInstance.h"
#include "../../UI/UIManager.h"
#include "../../UI/Main/MainWidget.h"
#include "../../Monster/MonsterStateComponent.h"
#include "../../gamemode/defaultgamestate.h"


AMonsterAIController::AMonsterAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	aiPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SetPerceptionComponent(*aiPerception);

	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("sight"));

	sightConfig->SightRadius = 800.f;
	sightConfig->LoseSightRadius = 800.f;

	sightConfig->PeripheralVisionAngleDegrees = 180.f;
	sightConfig->SetMaxAge(5.f);
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	aiPerception->ConfigureSense(*sightConfig);
	aiPerception->SetDominantSense(sightConfig->GetSenseImplementation());

	//static ConstructorHelpers::FObjectFinder<UBehaviorTree>
	//	MonsterTree(TEXT("/Script/AIModule.BehaviorTree'/Game/Monster/AI/BT_Monster.BT_Monster'"));
	//
	//if (MonsterTree.Succeeded())
	//	aiTree = MonsterTree.Object;

	SetGenericTeamId(FGenericTeamId(20));
}

void AMonsterAIController::BeginPlay()
{
	Super::BeginPlay();

	//if (aiTree)
	//	RunBehaviorTree(aiTree);

	aiPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnTargetUpdate);
	//aiPerception->OnPerceptionUpdated.AddDynamic(this, &AMonsterAIController::OnUpdate);
	//aiPerception->OnTargetPerceptionForgotten.AddDynamic(this, &AMonsterAIController::OnTargetForgotten);
	//aiPerception->OnTargetPerceptionInfoUpdated.AddDynamic(this, &AMonsterAIController::OnTargetInfoUpdate);
}

void AMonsterAIController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Pattern(DeltaTime);
}

ETeamAttitude::Type AMonsterAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* otherTeam = Cast<const IGenericTeamAgentInterface>(&Other);

	if (!otherTeam) return ETeamAttitude::Neutral;
	else
	{
		if (otherTeam->GetGenericTeamId().GetId() == 255)
			return ETeamAttitude::Neutral;
	}
	
	return GetGenericTeamId() == otherTeam->GetGenericTeamId().GetId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

void AMonsterAIController::OnTargetUpdate(AActor* actor, FAIStimulus AIStuimulus)
{

	if (GWorld->GetGameState<ADefaultGameState>()->IsPlayerLive())
	{
		if (AIStuimulus.WasSuccessfullySensed())
			target = actor;
		else
			target = nullptr;
	}

}

void AMonsterAIController::OnUpdate(const TArray<AActor*>& UpdatedActors)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("OnUpdate"));
}

void AMonsterAIController::OnTargetForgotten(AActor* actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("OnTargetForgotten"));
}

void AMonsterAIController::OnTargetInfoUpdate(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, TEXT("OnTargetInfoUpdate"));
}

void AMonsterAIController::PlayerDead()
{
	//Blackboard->SetValueAsBool(TEXT("PlayerLive"), false);
}

void AMonsterAIController::Attack()
{

	AMonster* Monster = GetPawn<AMonster>();
	if (IsValid(Monster))
	{

		FRotator lookAt = GetTargetRotator(GetPawn<AMonster>()->GetActorLocation(), target->GetActorLocation());
		Monster->SetActorRotation(lookAt);
		Monster->Attack();
	}
}

void AMonsterAIController::Ranged()
{

	AMonster* Monster = GetPawn<AMonster>();
	if (IsValid(Monster))
	{
		FRotator lookAt = GetTargetRotator(GetPawn<AMonster>()->GetActorLocation(), target->GetActorLocation());
		Monster->SetActorRotation(lookAt);
		Monster->Ranged();
	}
}

void AMonsterAIController::LookAround(float DeltaTime)
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

bool AMonsterAIController::Patrol()
{
	AMonster* monster =  GetPawn<AMonster>();


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

void AMonsterAIController::UpdateCapsule()
{
	FVector srcLocation, destLocation;


	AMonster* Monster = GetPawn<AMonster>();
	if (IsValid(Monster))
	{
		srcLocation = Monster->GetActorLocation();
		UCapsuleComponent* capsule = Monster->GetCapsule();

		if (IsValid(capsule))
		{
			srcLocation.Z -= capsule->GetScaledCapsuleHalfHeight();

			if (IsValid(target))
			{
				destLocation = target->GetActorLocation();
				capsule = Cast<UCapsuleComponent>(target->GetRootComponent());

				if (IsValid(capsule))
					destLocation.Z -= capsule->GetScaledCapsuleHalfHeight();
			}
		}
	}
}

void AMonsterAIController::Pattern(float DeltaTime)
{

	if (target != nullptr)
	{

		if (!GWorld->GetGameState<ADefaultGameState>()->IsPlayerLive())
		{
			target = nullptr;
			return;
		}


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
				Attack();
				//Ranged();
				break;
			case EPathFollowingRequestResult::RequestSuccessful: // 인지
				Monster->SetAnimState(EMonsterAnimState::Run);
				Monster->EnableHUD(true);
				rangedCoolTime += DeltaTime;
				if (rangedCoolTime >= rangedCoolTimeMax)
				{
					Ranged();
					rangedCoolTime = 0.f;
				}
				break;
			}
		}
	}
	else
	{
		if (Patrol())
		{
			LookAround(DeltaTime);
		}
		AMonster* Monster = GetPawn<AMonster>();
		if (Monster)
		{
			Monster->EnableHUD(false);

		}
	}
}


void AMonsterAIController::SetSightRadius(float Radius)
{
	//UAISenseConfig_Sight* sightConfig = aiPerception->GetSenseConfig<UAISenseConfig_Sight>();
	sightConfig->SightRadius = Radius;
	sightConfig->LoseSightRadius = Radius;
	//sightConfig->radi

	sightConfig->PeripheralVisionAngleDegrees = 180.f;
	sightConfig->SetMaxAge(5.f);
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = false;

	aiPerception->ConfigureSense(*sightConfig);
	aiPerception->SetDominantSense(sightConfig->GetSenseImplementation());
}

bool AMonsterAIController::IsTargetAttackDistance()
{

	if (target != nullptr)
	{

		AMonster* Monster = GetPawn<AMonster>();
		if (Monster)
		{
			float Distance = FMath::Abs(FVector::Distance(target->GetActorLocation(), Monster->GetActorLocation()));
			float monsterAttackDist = Monster->GetMonsterState()->GetAttackDistance();

			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("distance %f"), Distance));

			if (Distance <= monsterAttackDist + 50.f)
				return true;

		}
	}
	return false;
}
