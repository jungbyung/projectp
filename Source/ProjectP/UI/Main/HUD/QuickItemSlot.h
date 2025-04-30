// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultUICommon.h"
#include "InventorySlot.h"
#include "QuickItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UQuickItemSlot : public UInventorySlot
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
public:

	void SetQuickSlot(int32 Index);
	void Init();
	void UpdateSlot();
	void DragSlotColor(FLinearColor Color);
	void UseQuickSlot();
};
