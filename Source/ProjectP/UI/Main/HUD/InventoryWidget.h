// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../BaseUserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventoryWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton>		titleBar;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton>		closeButton;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class UInventorySlot>>	slots;

protected:
	virtual void NativeOnInitialized();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void Init();
	void UpdateSlots();

	UFUNCTION()
	void CloseButtonClick();

	UFUNCTION()
	void ChangeInventory(class UInventoryItem* Item, int32 Index);

	UFUNCTION()
	void HoveredItem(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, int32 Index);

	UFUNCTION()
	void TitleBarDown();

	UFUNCTION()
	void TitleBarUp();
};
