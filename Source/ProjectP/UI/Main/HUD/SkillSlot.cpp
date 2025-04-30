// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSlot.h"
#include "../../../Player/Skill/SkillInterface.h"
#include "../../../Player/PlayerCharacter.h"

void USkillSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	skillImage = Cast<UImage>(GetWidgetFromName(TEXT("SkillImage")));
	coolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("CoolTime")));
	coolTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoolTimeText")));
	skillKey = Cast<UTextBlock>(GetWidgetFromName(TEXT("SkillKey")));


}

void USkillSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);


	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ownerActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetSkillInfo(slotIndex);
	}
}

void USkillSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(ownerActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetSkillInfo(-1);
	}
}

void USkillSlot::Init()
{
	skillImage->SetBrushFromTexture(nullptr);
	skillImage->SetBrushTintColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
	coolTimeText->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
	coolTimeBar->SetPercent(0.f);
}

void USkillSlot::CoolTimeRatio(float CoolTimeRatio)
{
	coolTimeBar->SetPercent(CoolTimeRatio);
	coolTimeText->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	coolTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), CoolTimeRatio * coolTime)));
}

void USkillSlot::SetSkillTexture(UTexture2D* Texture)
{
	skillImage->SetBrushFromTexture(Texture);
	skillImage->SetBrushTintColor(FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f)));
	coolTimeBar->SetPercent(0.f);
}

void USkillSlot::SkillCoolTimeEnd()
{
	coolTimeText->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
}

void USkillSlot::SetSkillKey(int32 Index)
{
	skillKey->SetText(FText::FromString(FString::FromInt(Index)));
}
