// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultUICommon.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

	TObjectPtr<UTextBlock> itemName;
	TObjectPtr<UImage> itemIcon;
	TObjectPtr<UTextBlock> itemDesc;
	TObjectPtr<UTextBlock> itemType;
	TObjectPtr<UVerticalBox> itemOption;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UFont> font;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float fontSize = 14.f;

protected:
	virtual void NativeOnInitialized();
public:
	void SetItem(class UItemBase* Data);
	void SetSkill(class USkillBase* Skill);


};
