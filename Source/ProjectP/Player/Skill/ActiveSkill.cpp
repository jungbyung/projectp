// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveSkill.h"
#include "../DefaultPlayerController.h"
#include "../PlayerCharacter.h"
#include "../animation/PlayerAnimInstance.h"

UActiveSkill::UActiveSkill()
{
}

void UActiveSkill::Use()
{
	Super::Use();

	APlayerCharacter* player = Cast<APlayerCharacter>(ownerPawn);

	if (IsValid(player))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("use skill"));
		isActive = true;
		skillCool = 0.f;
		player->SetUpdateSkill(this);
		player->SetAnimState(EPlayerAnimState::Skill);
	}
}

void UActiveSkill::UpdateCoolTime(float DeltaTime)
{
	Super::UpdateCoolTime(DeltaTime);

	if (isActive)
	{
		skillCool += DeltaTime;
		if (skillIndex > -1)
			GWorld->GetFirstPlayerController<ADefaultPlayerController>()->SetSkillCoolTime(skillIndex, 1.f - skillCool / skillCoolTime);


		if (skillCool >= skillCoolTime)
		{
			isActive = false;
			skillCool = 0.f;
			GWorld->GetFirstPlayerController<ADefaultPlayerController>()->SkillCoolTimeEnd(skillIndex);

		}
	}

}

void UActiveSkill::UpdateEnd()
{
	Super::UpdateEnd();
}
