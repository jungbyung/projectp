// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../defaultuicommon.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> ownerActor;
	TObjectPtr<UImage> skillImage;
	TObjectPtr<UProgressBar> coolTimeBar;
	TObjectPtr<UTextBlock> coolTimeText;
	TObjectPtr<UTextBlock> skillKey;

	float coolTime = 0.f;
	int32 slotIndex = -1;
protected:

	virtual void NativeOnInitialized();
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

public:
	void Init();
	void CoolTimeRatio(float CoolTimeRatio);
	void SetCoolTime(float CoolTime) { coolTime = CoolTime; }
	void SetOwner(AActor* Actor) { ownerActor = Actor; }
	void SetSlotIndex(int32 Index) { slotIndex = Index; }

	void SetSkillTexture(UTexture2D* Texture);
	void SkillCoolTimeEnd();
	void SetSkillKey(int32 Index);


	
};
