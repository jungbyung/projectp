// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkillWidget.h"
#include "SkillSlot.h"
#include "../../../player/DefaultPlayerController.h"
#include "../../../player/PlayerCharacter.h"

void UPlayerSkillWidget::NativeOnInitialized()
{
	//skillSlots.Init(nullptr, 4);

	UDataTable* skillData = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_PlayerSkillData.DT_PlayerSkillData'"));

	if (IsValid(skillData))
	{
		FPlayerSkillData* Skill = skillData->FindRow<FPlayerSkillData>(TEXT("Shinobi"), TEXT(""));
		//GetWorld()->GetFirstPlayerController<ADefaultPlayerController>()->getplayer

		APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		for (int32 i = 0; i < Skill->skillOptions.Num(); ++i)
		{
			FString SkillSlotName = TEXT("WB_SkillSlot_") + FString::FromInt(i);

			USkillSlot* SkillSlot = Cast<USkillSlot>(GetWidgetFromName(*SkillSlotName));
			if (SkillSlot)
			{
				SkillSlot->Init();
				SkillSlot->SetSkillTexture(Skill->skillOptions[i].icon);
				SkillSlot->SetCoolTime(Skill->skillOptions[i].coolTime);
				SkillSlot->SetSlotIndex(i);
				SkillSlot->SetSkillKey(i + 1);
				//SkillSlot->SetOwner(ownerActor);


				if (player)
				{
					player->SetSkillOption(Skill->skillOptions[i], i);
					player->SetSkillCoolTime(i, Skill->skillOptions[i].coolTime);
					player->SetSkillUseStamina(i, Skill->skillOptions[i].stamina);
				}
				skillSlots.Add(SkillSlot);
			}
		}
	}

}

void UPlayerSkillWidget::Init()
{

	for (int32 i = 0; i < skillSlots.Num(); ++i)
	{
		skillSlots[i]->SetOwner(ownerActor);
	}

}

void UPlayerSkillWidget::SetSkillCoolTime(int32 Index, float Ratio)
{
	if (skillSlots[Index])
	{
		skillSlots[Index]->CoolTimeRatio(Ratio);
	}
}

void UPlayerSkillWidget::SkillCoolTimeEnd(int32 Index)
{
	if (skillSlots[Index])
		skillSlots[Index]->SkillCoolTimeEnd();
}	
