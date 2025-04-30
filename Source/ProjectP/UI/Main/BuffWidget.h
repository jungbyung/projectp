// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../baseUserWidget.h"
#include "BuffWidget.generated.h"



/**
 * 
 */
UCLASS()
class PROJECTP_API UBuffWidget : public UBaseUserWidget
{
	GENERATED_BODY()
protected:
	TArray<TObjectPtr<class UBuffSlot>> slots;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UBuffSlot> buffSlotClass;

	TObjectPtr<UHorizontalBox> buffList;


protected:
	virtual void NativeOnInitialized();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void AddBuff(class UItemBase* ItemBase);

	void RemoveBuffList(class UBuffSlot* BuffSlot);
};
