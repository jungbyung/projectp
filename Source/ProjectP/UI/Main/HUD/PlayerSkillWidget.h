// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../BaseUserWidget.h"
#include "PlayerSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerSkillWidget : public UBaseUserWidget
{
	GENERATED_BODY()
protected:
	TArray<TObjectPtr<class USkillSlot>> skillSlots;
protected:
	virtual void NativeOnInitialized();
public:
	void Init();
	void SetSkillCoolTime(int32 Index, float Ratio);
	void SkillCoolTimeEnd(int32 Index);
};
