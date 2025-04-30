// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickItemSlot.h"
#include "../../../Player/Inventory/InventoryInterface.h"
#include "../../../Player/Inventory/inventorycomponent.h"
#include "../../../Item/inventoryitem.h"
#include "../itemdragdropslot.h"

void UQuickItemSlot::NativeOnInitialized()
{
	icon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	slotBackGround = Cast<UImage>(GetWidgetFromName(TEXT("SlotBackGround")));
}

FReply UQuickItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply	result;
	result.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	//{
	//	IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);
	//
	//	if (InvenInterface)
	//	{
	//		UInventoryComponent* InvenComp = InvenInterface->GetInventoryComponent();
	//
	//		if (InvenComp)
	//		{
	//			if (InvenComp->IsItemValid(slotIndex))
	//			{
	//				result = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	//			}
	//		}
	//	}
	//}


	return result.NativeReply;
}


void UQuickItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	//
	//if (!OutOperation)
	//{
	//	UItemDragDropSlot* DragSlot = Cast<UItemDragDropSlot>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropSlot::StaticClass()));
	//	OutOperation = DragSlot;
	//
	//	if (IsValid(DragSlot))
	//	{
	//		UInventorySlot* DragWidget = CreateWidget<UInventorySlot>(GetWorld(), dragWidgetClass);
	//
	//		if (DragWidget)
	//		{
	//			DragWidget->SetOwnerActor(ownerActor);
	//			DragWidget->SetSlotIndex(slotIndex);
	//			DragWidget->Init();
	//			DragWidget->DragSlotColor(FLinearColor(0.f, 0.f, 0.f, 0.f));
	//
	//			DragSlot->DefaultDragVisual = DragWidget;
	//			DragSlot->prevSlotIndex = slotIndex;
	//			DragSlot->Pivot = EDragPivot::MouseDown;
	//			icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.4f));
	//		}
	//	}
	//}
}

bool UQuickItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	
	UItemDragDropSlot* DragSlot = Cast<UItemDragDropSlot>(InOperation);
	if (DragSlot)
	{
		IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

		if (InvenInterface)
		{
			UInventoryComponent* Inventory = InvenInterface->GetInventoryComponent();
			if (Inventory)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("quick drop"));
				Inventory->SetQuickItem(DragSlot->prevSlotIndex);
				Inventory->SetDrag(false);
				DragSlotColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
			}
		}
		return true;
	}

	return false;
}

void UQuickItemSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UQuickItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

}

void UQuickItemSlot::SetQuickSlot(int32 Index)
{
	if (!IsValid(icon) || slotIndex == -1)
		return;

	IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

	if (inventoryInterface)
	{
		UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

		if (inventory)
		{
			TArray<TObjectPtr<UInventoryItem>> itemList = inventory->GetItemList();

			if (itemList.IsValidIndex(slotIndex))
			{
				if (IsValid(itemList[slotIndex]))
				{
					icon->SetBrushFromTexture(itemList[slotIndex]->itemBase->icon);
					icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 1.f));

				}
				else
				{
					//icon->SetBrushFromTexture(nullptr);
					icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.4f));
				}
			}
		}
	}
}

void UQuickItemSlot::Init()
{
}

void UQuickItemSlot::UpdateSlot()
{
	if (!IsValid(icon) || slotIndex == -1)
		return;

	IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

	if (inventoryInterface)
	{
		UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

		if (inventory)
		{
			TArray<TObjectPtr<UInventoryItem>> itemList = inventory->GetItemList();

			if (itemList.IsValidIndex(slotIndex))
			{
				if (IsValid(itemList[slotIndex]))
				{
					icon->SetBrushFromTexture(itemList[slotIndex]->itemBase->icon);
					icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
				}
				else
				{
					//icon->SetBrushFromTexture(nullptr);
					icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.4f));
				}
			}
		}
	}
}

void UQuickItemSlot::DragSlotColor(FLinearColor Color)
{
}

void UQuickItemSlot::UseQuickSlot()
{

}
