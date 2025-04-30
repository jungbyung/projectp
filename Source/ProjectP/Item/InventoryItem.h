// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffItem, int32);

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventoryItem : public UObject
{
	GENERATED_BODY()
public:
	UInventoryItem();

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UItemBase> itemBase;
	FOnBuffItem buffDelegate;
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UBuffSlot> buffSlot = nullptr;

//private:
//	TObjectPtr<class ADecalRotation> areaDecal;
protected:
	float duration;
	float CurrentDuration;

	bool isUse = false;
	int32 quickItemIndex = -1;
	int32 buffIndex = -1;
public:
	void SetDuration(float Duration) { duration = Duration; }
	void Update(float DeltaTime);

	void UseItem();
	bool IsUse() { return isUse; }

	void SetItem(class UItemBase* Item);
	void SetBuffItemIndex(int32 Index) { buffIndex = Index; }

	void setQuickItemIndex(int32 Index) { quickItemIndex = Index; }
	int32 GetQuickItemIndex() { return quickItemIndex; }

	class UItemBase* GetItem();
	void SetBuffSlot(class UBuffSlot* BuffSlot);
};
  