// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../BaseUserWidget.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemSlotWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	TObjectPtr<class UQuickItemSlot> quickItem;
public:
	void Init();

	UFUNCTION()
	void SetQuickItem(int32 Index);

	UFUNCTION()
	void UseQuickItem();
};
