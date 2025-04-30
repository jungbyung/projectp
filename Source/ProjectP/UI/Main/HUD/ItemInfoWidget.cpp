// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWidget.h"
#include "../../../item/itembase.h"
#include "../../../Player/Skill/SkillBase.h"

void UItemInfoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	itemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemName")));
	itemIcon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	itemDesc = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemDesc")));
	itemOption = Cast<UVerticalBox>(GetWidgetFromName(TEXT("ItemOption")));
}

void UItemInfoWidget::SetItem(UItemBase* Data)
{
	itemName->SetText(FText::FromString(Data->itemName));
	itemIcon->SetBrushFromTexture(Data->icon);
	//itemType->SetText(FText::FromString(Data->data.type));
	itemDesc->SetText(Data->desc);
	
	itemOption->ClearChildren();
	
	int32 count = Data->options.Num();
	
	for (int32 i = 0; i < count; ++i)
	{
		UTextBlock* option = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
	
		option->Font.Size = fontSize;
		option->Font.FontObject = font;
		itemOption->AddChild(option);
	
		UVerticalBoxSlot* verticalBoxSlot = Cast<UVerticalBoxSlot>(option->Slot);
	
		verticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
		verticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		verticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	
		FString optionName;// GetItemOptionString(Data->data.optionarray[i].option);
		
		//optionName += TEXT(" : ") + FString::SanitizeFloat(Data->GetItemOption()[i].increase);
	
		if (Data->options[i].duration > 0)
		{
			optionName = TEXT("증가량 : ") + FString::Printf(TEXT("%.0f"), Data->options[i].increase);
			optionName += TEXT("\n지속시간 : ") + FString::SanitizeFloat(Data->options[i].duration) + TEXT(" 초");
		}
		else
		{
			optionName = TEXT("회복량 : ") + FString::Printf(TEXT("%.0f"), Data->options[i].increase);
		}
		option->SetText(FText::FromString(optionName));
	}
}

void UItemInfoWidget::SetSkill(USkillBase* Skill)
{

	itemName->SetText(FText::FromString(Skill->GetSkillOption().skillName));
	itemIcon->SetBrushFromTexture(Skill->GetSkillOption().icon);
	itemDesc->SetText(FText::FromString(Skill->GetSkillOption().desc));

	itemOption->ClearChildren();

	//int32 count = Data->GetItemOption().Num();

	UTextBlock* option = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	option->Font.Size = fontSize;
	option->Font.FontObject = font;
	itemOption->AddChild(option);

	UVerticalBoxSlot* verticalBoxSlot = Cast<UVerticalBoxSlot>(option->Slot);

	verticalBoxSlot->SetSize(FSlateChildSize(ESlateSizeRule::Automatic));
	verticalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	verticalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	FString optionName = TEXT("공격력 : ") +  FString::Printf(TEXT("%d\n"), Skill->GetSkillOption().attackPower);
	optionName += TEXT("스테미나 소모량 : ") + FString::Printf(TEXT("%d\n"), Skill->GetSkillOption().stamina);
	optionName += TEXT("재사용 대기시간 : ") + FString::Printf(TEXT("%.1f\n"), Skill->GetSkillOption().coolTime);
	option->SetText(FText::FromString(optionName));
	
}
