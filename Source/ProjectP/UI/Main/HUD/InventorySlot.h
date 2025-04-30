// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultUICommon.h"
#include "../../../DefaultGameCommon.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> ownerActor;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UImage> icon;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> count;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UImage> slotBackGround;
	UPROPERTY(VisibleAnywhere)
	int32 slotIndex = -1;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UInventorySlot> dragWidgetClass;
public:
	void SetOwnerActor(AActor* OwnerActor) { ownerActor = OwnerActor; }
	void SetSlotIndex(int32 Index) { slotIndex = Index; }
	
protected:

	virtual void NativeOnInitialized();
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnDragDetected(const FGeometry& InGeometry,const FPointerEvent& InMouseEvent,UDragDropOperation*& OutOperation);
	virtual bool NativeOnDrop(const FGeometry& InGeometry,const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation);
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
public:

	void Init();
	void UpdateSlot();
	void DragSlotColor(FLinearColor Color);
};
