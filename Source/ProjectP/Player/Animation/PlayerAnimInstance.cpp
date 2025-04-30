// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../PlayerCharacter.h"
#include "../../GameMode/DefaultGameState.h"

UDataTable* UPlayerAnimInstance::animData = nullptr;

UPlayerAnimInstance::UPlayerAnimInstance()
{
	if (!animData)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			animTableAsset(TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_PlayerAnim.DT_PlayerAnim'"));

		if (animTableAsset.Succeeded())
			animData = animTableAsset.Object;
	}
}

void UPlayerAnimInstance::PostInitProperties()
{
	Super::PostInitProperties();

	if (!animName.IsNone())
	{
		UPlayerAnimInstance* cdo = Cast<UPlayerAnimInstance>(GetClass()->GetDefaultObject());

		if (cdo)
		{
			const FPlayerAnimData* playerAnimData = animData->FindRow<FPlayerAnimData>(animName, TEXT(""));

			if (playerAnimData)
			{
				cdo->animMap = playerAnimData->animMap;
				cdo->locomotionMap = playerAnimData->locomotionMap;
				cdo->attackMontage = playerAnimData->attackMontage;
				cdo->attackSectionNameArray = playerAnimData->attackSectionNameArray;
			}
		}
	}
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnMontageEnded.AddDynamic(this, &UPlayerAnimInstance::MontageEnd);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		UCharacterMovementComponent* movement = player->GetCharacterMovement();

		if (IsValid(movement))
		{
			speed = movement->Velocity.Length();
		}
	}

}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		player->NormalAttack();
	}
}

void UPlayerAnimInstance::AnimNotify_RightWeapon()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		player->SetRightWeapon();
	}
}

void UPlayerAnimInstance::AnimNotify_LeftWeapon()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		player->SetLeftWeapon();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackCombo()
{
	isAttackCombo = true;
}

void UPlayerAnimInstance::AnimNotify_HitEnd()
{
	hitAlpha = 0.f;
}

void UPlayerAnimInstance::AnimNotify_SkillEnd()
{
	skillIndex = -1;
	playerAnimState = EPlayerAnimState::Locomotion;

	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		player->SetUpdateSkill(nullptr);
	}
}

void UPlayerAnimInstance::AnimNotify_DodgeEnd()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("dodgeEnd"));
	//playerAnimState = EPlayerAnimState::Locomotion;
}

void UPlayerAnimInstance::MontageEnd(UAnimMontage* Montage, bool Interrupted)
{
	if (Montage == attackMontage)
	{
		if (!Interrupted)
		{
			isAttack = false;
			isAttackCombo = false;
			attackSectionIndex = 0;
			playerAnimState = EPlayerAnimState::Locomotion;
		}
	}
}

void UPlayerAnimInstance::AnimNotify_SkillAttack()
{

	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
	{
		player->SkillAttack();
	}
}

void UPlayerAnimInstance::AnimNotify_Block()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
		player->BlockIn();
}

void UPlayerAnimInstance::AnimNotify_BlockOut()
{
	playerAnimState = EPlayerAnimState::Locomotion;

	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
		player->BlockOut();
}

void UPlayerAnimInstance::AnimNotify_BlockCounter()
{
	APlayerCharacter* player = Cast<APlayerCharacter>(TryGetPawnOwner());

	if (IsValid(player))
		player->NormalAttack();
}

void UPlayerAnimInstance::AnimNotify_BlockCounterEnd()
{
	playerAnimState = EPlayerAnimState::Locomotion;
}

void UPlayerAnimInstance::AnimNotify_HitStunEnd()
{
	playerAnimState = EPlayerAnimState::Locomotion;
}

void UPlayerAnimInstance::AnimNotify_BlockHitEnd()
{
	blockAnimState = EBlock::Loop;

	if (toLocomotion)
		playerAnimState = EPlayerAnimState::Locomotion;

}

void UPlayerAnimInstance::AnimNotify_NormalStaggerAttack()
{
}


void UPlayerAnimInstance::SetAnimData(const FName& Name)
{
	const FPlayerAnimData* playerAnimData = animData->FindRow<FPlayerAnimData>(Name, TEXT(""));

	if (playerAnimData)
	{
		animMap = playerAnimData->animMap;
		attackMontage = playerAnimData->attackMontage;
		attackSectionNameArray = playerAnimData->attackSectionNameArray;
	}
}

void UPlayerAnimInstance::SetDir(EWalkDirection Direction)
{
	dir = Direction;
}

void UPlayerAnimInstance::SetSpeed(float Speed)
{
	speed = Speed;
}

void UPlayerAnimInstance::SetRun(bool Run)
{
	isRun = Run;
}


void UPlayerAnimInstance::Counter()
{
	playerAnimState = EPlayerAnimState::BlockCounter;
}

void UPlayerAnimInstance::BlockIn()
{
	if (playerAnimState == EPlayerAnimState::Locomotion)
	{
		toLocomotion = false;
		playerAnimState = EPlayerAnimState::Block;
		blockAnimState = EBlock::In;
	}
}

void UPlayerAnimInstance::BlockOut()
{
	if(playerAnimState == EPlayerAnimState::Block)
		blockAnimState = EBlock::Out;
}

void UPlayerAnimInstance::BlockHit()
{

	if (playerAnimState == EPlayerAnimState::Block)
		blockAnimState = EBlock::Hit;
}

void UPlayerAnimInstance::BlockHit2Locomotion(bool Locomotion)
{
	toLocomotion = Locomotion;
	BlockHit();
}

void UPlayerAnimInstance::Dead()
{
	playerAnimState = EPlayerAnimState::Dead;

	GWorld->GetGameState<ADefaultGameState>()->PlayerLive(false);
}

void UPlayerAnimInstance::HitDirection(EDirection HitDirection)
{
	playerAnimState = EPlayerAnimState::NormalStagger;
	hitDir = HitDirection;
}

void UPlayerAnimInstance::Attack()
{
	if (!IsValid(attackMontage))
		return;

	playerAnimState = EPlayerAnimState::Attack;

	if (!Montage_IsPlaying(attackMontage))
	{
		Montage_SetPosition(attackMontage, 0.f);
		Montage_Play(attackMontage);
		attackSectionIndex = 0;
		Montage_JumpToSection(attackSectionNameArray[attackSectionIndex]);
		attackSectionIndex = (attackSectionIndex + 1) % attackSectionNameArray.Num();
	}
	else if (Montage_IsPlaying(attackMontage))
	{
		if (isAttackCombo)
		{
			Montage_Play(attackMontage);
			Montage_JumpToSection(attackSectionNameArray[attackSectionIndex]);
			attackSectionIndex = (attackSectionIndex + 1) % attackSectionNameArray.Num();
			isAttackCombo = false;
		}
	}
}
