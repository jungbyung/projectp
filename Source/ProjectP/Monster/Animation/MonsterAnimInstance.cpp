// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "../ai/MonsterAIController.h"
#include "../ai/EpicMonsterAIController.h"
#include "../monster.h"

UDataTable* UMonsterAnimInstance::animData = nullptr;

UMonsterAnimInstance::UMonsterAnimInstance()
{

	if (!animData)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			animTableAsset(TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_MonsterAnim.DT_MonsterAnim'"));

		if (animTableAsset.Succeeded())
			animData = animTableAsset.Object;
	}

}

void UMonsterAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();

	if (!animName.IsNone())
	{
		UMonsterAnimInstance* cdo = Cast<UMonsterAnimInstance>(GetClass()->GetDefaultObject());

		if (cdo)
		{
			const FMonsterAnimData* MonsterAnimData = animData->FindRow<FMonsterAnimData>(animName, TEXT(""));
			
			if (MonsterAnimData)
			{
				cdo->animMap = MonsterAnimData->animMap;
				cdo->attackMontage = MonsterAnimData->attackMontage;
				cdo->attackSectionNameArray = MonsterAnimData->attackSectionNameArray;
				cdo->rangedMontage = MonsterAnimData->rangedMontage;
				cdo->rangedSectionNameArray = MonsterAnimData->rangedSectionNameArray;
			}
		}
	}

}

void UMonsterAnimInstance::NativeBeginPlay()
{
	OnMontageEnded.AddDynamic(this, &UMonsterAnimInstance::MontageEnd);
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	monsterAnimState = EMonsterAnimState::Idle;
	attackRnd = -1;
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	bIsStaggerAttack = false;

	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->NormalAttack();
}

void UMonsterAnimInstance::AnimNotify_HitEnd()
{
	hitAlpha = 0.f;
}

void UMonsterAnimInstance::AnimNotify_Dead()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->EnableDissolve();
}

void UMonsterAnimInstance::AnimNotify_Cast()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->UseSkill();
}

void UMonsterAnimInstance::AnimNotify_CastEnd()
{
	monsterAnimState = EMonsterAnimState::Idle;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("cast end"));
}

void UMonsterAnimInstance::AnimNotify_NormalStaggerAttack()
{
	bIsStaggerAttack = true;

	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->NormalStaggerAttack();
}

void UMonsterAnimInstance::MontageEnd(UAnimMontage* Montage, bool Interrupted)
{

	if (Montage == attackMontage ||
		Montage == rangedMontage)
	{
		if (!Interrupted)
		{
			monsterAnimState = EMonsterAnimState::Idle;
		}
	}
}

void UMonsterAnimInstance::AnimNotify_Fire()
{
	///Script/Engine.ParticleSystem'/Game/ParagonProps/FX/Particles/Core/P_SingleTargetCore_Projectile.P_SingleTargetCore_Projectile'

	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->Fire();
}

void UMonsterAnimInstance::AnimNotify_Breath()
{

	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
		monster->Breath();
}

void UMonsterAnimInstance::AnimNotify_DodgeEnd()
{

	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (IsValid(monster))
	{
		monster->DodgeCoolInit();
		monsterAnimState = EMonsterAnimState::Idle;
	}

}

void UMonsterAnimInstance::AnimNotify_DodgeMoveEnd()
{
}

void UMonsterAnimInstance::SetAnimState(EMonsterAnimState MonsterAnimState)
{
	monsterAnimState = MonsterAnimState;
}


void UMonsterAnimInstance::AttackRand()
{
	attackRnd = FMath::RandRange(0, 1);
}

void UMonsterAnimInstance::SkillRand()
{
	skillRand = FMath::RandRange(0, 1);
}

void UMonsterAnimInstance::AttackMontage()
{

	if (!IsValid(attackMontage))
		return;

	if (!Montage_IsPlaying(attackMontage))
	{
		attackSectionIndex = FMath::Rand() % attackSectionNameArray.Num();
		Montage_SetPosition(attackMontage, 0.f);
		Montage_Play(attackMontage);
		Montage_JumpToSection(attackSectionNameArray[attackSectionIndex]);
	}
}

void UMonsterAnimInstance::AttackMontage(int32 Index)
{
	if (!IsValid(attackMontage) || Index >= attackSectionNameArray.Num())
		return;

	if (!Montage_IsPlaying(attackMontage))
	{
		Montage_SetPosition(attackMontage, 0.f);
		Montage_Play(attackMontage);
		Montage_JumpToSection(attackSectionNameArray[Index]);
	}
}

void UMonsterAnimInstance::RangedMontage()
{
	if (!IsValid(rangedMontage))
		return;

	if (!Montage_IsPlaying(rangedMontage))
	{
		rangedSectionIndex = FMath::Rand() % rangedSectionNameArray.Num();
		Montage_SetPosition(rangedMontage, 0.f);
		Montage_Play(rangedMontage);
		Montage_JumpToSection(rangedSectionNameArray[rangedSectionIndex]);
	}
}

bool UMonsterAnimInstance::AttackPattern()
{
	AMonster* monster = Cast<AMonster>(TryGetPawnOwner());
	if (bIsFollowUpAttack)
	{
		bIsFollowUpAttack = false;
		if (followUpAttackIndex > 0 && followUpAttackIndex < attackSectionNameArray.Num())
		{
			AttackMontage(followUpAttackIndex);
			followUpAttackIndex = -1;
			return true;
		}
	}
	return false;
}

void UMonsterAnimInstance::SetHitDirection(EDirection HitDirection)
{
	hitDirection = HitDirection;
}
