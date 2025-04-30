// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Animation/MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"
#include "../GameMode/DefaultGameState.h"
#include "../UI/main/hud/HeadWidget.h"
#include "monsterspawner.h"
#include "Camera/PlayerCameraManager.h"
#include "../Common/FootIKComponent.h"
#include "../item/ItemBox.h"

#include "../ui/Main/MainWidget.h"
#include "../ui/main/HUD/HUDMonsterWidget.h"
#include "../ui/UIManager.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("body"));
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh"));
	movement = CreateDefaultSubobject<UMonsterMovementComponent>(TEXT("movement"));
	stateComponent = CreateDefaultSubobject<UMonsterStateComponent>(TEXT("state"));
	widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("widget"));
	footIK = CreateDefaultSubobject<UFootIKComponent>(TEXT("footIK"));
	footIK->SetOwner(this, mesh);
	footIK->SetOwnerOffset(body->GetUnscaledCapsuleHalfHeight());

	SetRootComponent(body);

	mesh->SetupAttachment(body);
	movement->SetUpdatedComponent(body);

	body->bNavigationRelevant = false;
	body->SetCanEverAffectNavigation(false);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMonsterAIController::StaticClass();

	bUseControllerRotationYaw = true;

	body->SetCollisionProfileName(TEXT("Monster"));
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//mesh->SetReceivesDecals(false);
	 

}

void AMonster::SetFootIkInfo(const FFootIKResult& FootIKL, const FFootIKResult& FootIKR)
{
	animInst->SetFootIkInfo(FootIKL, FootIKR);
}

void AMonster::SetRootCapsuleHalfHeight(float Height)
{
	body->SetCapsuleHalfHeight(Height);
}

float AMonster::GetRootCapsuleHalfHeight()
{
	return body->GetScaledCapsuleHalfHeight();
}

void AMonster::SetFootRotation(const FRotator& Left, const FRotator& Right)
{
	animInst->SetFootRotation(Left, Right);
}

void AMonster::SetHipOffset(float Offset)
{
	animInst->SetHipOffset(Offset);
}

void AMonster::SetFootOffset(float Left, float Right)
{
	animInst->SetFootOffset(Left, Right);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	int32 matCount = mesh->GetNumMaterials();

	for (int32 i = 0; i < matCount; ++i)
	{
		UMaterialInstanceDynamic* matInst = mesh->CreateDynamicMaterialInstance(i);
		materialArray.Add(matInst);
	}


	animInst = Cast<UMonsterAnimInstance>(mesh->GetAnimInstance());
	
	if (movement)
	//	movement->MaxSpeed = stateComponent->GetWalkSpeed();
		movement->SetMaxSpeed(stateComponent->GetWalkSpeed());

	if (stateComponent->GetGrade() == EMonsterGrade::Normal)
	{
		headWidget = CreateWidget<UHeadWidget>(GetWorld(), headWidgetClass);

		if (IsValid(headWidget))
			widget->SetWidget(headWidget);

		headWidget->SetName(FText::FromName(stateComponent->GetRowName()));
	}
}

void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (spawner)
		spawner->DestroySpawnMonster();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GWorld->GetGameState<ADefaultGameState>()->IsPlayerLive())
	{
		GetController< AMonsterAIController>()->PlayerDead();
	}

	if (dissolveEnable)
	{
		dissolveTime += DeltaTime;

		dissolve = 1.f - dissolveTime / dissolveTimeMax * 2.f;

		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("dissolve %f"), dissolve));

		int32 matCount = materialArray.Num();

		for (int32 i = 0; i < matCount; ++i)
		{
			materialArray[i]->SetScalarParameterValue(TEXT("Dissolve"), dissolve);

		}
		if (dissolveTime >= dissolveTimeMax)
		{
			Dead();
		}
	}

}

void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	dmg -= stateComponent->GetDefense();
	dmg = dmg < 1.f ? 1.f : dmg;

	stateComponent->AddHP((int32)-dmg);

	if (stateComponent->GetGrade() != EMonsterGrade::Normal)
	{
		UMainWidget* MainWidget = CUIManager::GetInstance()->FindWidget<UMainWidget>(TEXT("UI_Main"));
		if (MainWidget)
		{
			MainWidget->SetMonsterHPRatio(stateComponent->GetHP() / (float)stateComponent->GetHPMax());
			MainWidget->SetMonsterNameText(stateComponent->GetName());
			//MainWidget->VisibleMonsterHPHUD(true);
		}
	}
	else
	{
		headWidget->SetHPRatio(stateComponent->GetHP() / (float)stateComponent->GetHPMax());
	}

	if (stateComponent->GetHP() <= 0)
	{
		SetAnimState(EMonsterAnimState::Death);
		body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetController<AAIController>()->StopMovement();
		DropItem();
		//GetController<AAIController>()->BrainComponent->StopLogic(TEXT("Death"));
	}
	else
		animInst->Hit();


	return dmg;
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::EnableDissolve()
{
	dissolveEnable = true;

	int32 matCount = materialArray.Num();

	for (int32 i = 0; i < matCount; ++i)
	{
		materialArray[i]->SetScalarParameterValue(TEXT("DissolveEnable"), 1.f);
	}


}

void AMonster::SetLocomotion()
{
	animInst->SetAnimState(EMonsterAnimState::Idle);
}

void AMonster::SetDodge()
{
	animInst->SetAnimState(EMonsterAnimState::Dodge);
}

void AMonster::Dead()
{
	Destroy();
}

void AMonster::DropItem()
{
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AItemBox* item = GetWorld()->SpawnActor<AItemBox>(AItemBox::StaticClass(), GetActorLocation(), GetActorRotation(), Param);
	item->RandItem();

	USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
		TEXT("/Script/Engine.SoundWave'/Game/Sound/1/Bag_Handle_1-5.Bag_Handle_1-5'"));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, GetActorLocation(), GetActorRotation());
}

void AMonster::SetAIPatrolEnable()
{
	AAIController* controller = GetController<AAIController>();

	if (IsValid(Controller))
		controller->GetBlackboardComponent()->SetValueAsBool(TEXT("PatrolEnable"), EnablePatrolPosArray());
}

void AMonster::SetSpawner(AMonsterSpawner* Spawner)
{
	spawner = Spawner;
}

void AMonster::EnableHUD(bool Enable)
{
	if (stateComponent->GetGrade() == EMonsterGrade::Boss)
	{
		if (CUIManager::GetInstance())
		{
			UMainWidget* MainWidget = CUIManager::GetInstance()->FindWidget<UMainWidget>(TEXT("UI_Main"));
			if (MainWidget)
			{
				MainWidget->VisibleMonsterHPHUD(Enable);
				MainWidget->SetMonsterHPRatio(stateComponent->GetHP() / (float)stateComponent->GetHPMax());
				MainWidget->SetMonsterNameText(stateComponent->GetName());
			}
		}
	}
}

void AMonster::SetAnimState(EMonsterAnimState AnimState)
{
	animInst->SetAnimState(AnimState); 
}

void AMonster::NormalAttack()
{
}

void AMonster::NormalStunAttack()
{
}

void AMonster::NormalStaggerAttack()
{
}

void AMonster::Attack()
{
	animInst->SetAnimState(EMonsterAnimState::Attack);
	animInst->AttackRand();
}

void AMonster::Ranged()
{
}

void AMonster::Skill()
{
	animInst->SetAnimState(EMonsterAnimState::Skill);
}

void AMonster::UseSkill()
{
}

void AMonster::Fire()
{
}

void AMonster::Breath()
{
}

void AMonster::FrontDodgeThrust()
{
}

void AMonster::DodgeCoolInit()
{
	movement->DodgeInit();
}

bool AMonster::IsAttackDistance()
{
	AMonsterAIController* control = GetController<AMonsterAIController>();

	if (control)
	{
		return control->IsTargetAttackDistance();
	}

	return false;
}

