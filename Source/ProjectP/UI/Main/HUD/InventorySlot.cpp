// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "../../../Player/Inventory/InventoryInterface.h"
#include "../../../Player/Inventory/inventorycomponent.h"
#include "../../../Item/inventoryitem.h"
#include "../../../Item/itembase.h"
#include "../itemdragdropslot.h"

void UInventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	icon = Cast<UImage>(GetWidgetFromName(TEXT("ItemIcon")));
	slotBackGround = Cast<UImage>(GetWidgetFromName(TEXT("SlotBackGround")));
	count = Cast<UTextBlock>(GetWidgetFromName(TEXT("Count")));
}

FReply UInventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply	result;
	result.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

		if (InvenInterface)
		{
			UInventoryComponent* InvenComp = InvenInterface->GetInventoryComponent();

			if (InvenComp)
			{
				if (InvenComp->IsItemValid(slotIndex))
				{
					InvenComp->SetDrag(true);
					result = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
				}
			}
		}
	}


	return result.NativeReply;
}

FReply UInventorySlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply	result;
	result.NativeReply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

		if (InvenInterface)
		{
			UInventoryComponent* Inventory = InvenInterface->GetInventoryComponent();

			if (Inventory)
			{
				if (Inventory->IsItemValid(slotIndex))
				{
					Inventory->UseItem(slotIndex);
				}
			}
		}
	}

	return result.NativeReply;
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (!OutOperation)
	{
		UItemDragDropSlot* DragSlot = Cast<UItemDragDropSlot>(UWidgetBlueprintLibrary::CreateDragDropOperation(UItemDragDropSlot::StaticClass()));
		OutOperation = DragSlot;

		if (IsValid(DragSlot))
		{
			UInventorySlot* DragWidget = CreateWidget<UInventorySlot>(GetWorld(), dragWidgetClass);

			if (DragWidget)
			{
				DragWidget->SetOwnerActor(ownerActor);
				DragWidget->SetSlotIndex(slotIndex);
				DragWidget->Init();
				DragWidget->DragSlotColor(FLinearColor(0.f, 0.f, 0.f, 0.f));

				DragSlot->DefaultDragVisual = DragWidget;
				DragSlot->prevSlotIndex = slotIndex;
				DragSlot->Pivot = EDragPivot::MouseDown;
				icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.4f));
			}
		}
	}
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UItemDragDropSlot* DragSlot = Cast<UItemDragDropSlot>(InOperation);
	if (DragSlot)
	{
		IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

		if (InvenInterface)
		{
			UInventoryComponent* Inventory = InvenInterface->GetInventoryComponent();
			if (Inventory)
			{
				Inventory->SwapItem(DragSlot->prevSlotIndex, slotIndex);
				Inventory->SetDrag(false);
				DragSlotColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
			}
		}
		return true;
	}

	return false;
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("hoverd"));


	IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

	if (InvenInterface)
	{
		UInventoryComponent* Inventory = InvenInterface->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->SetItemInfo(slotIndex);
		}
	}

}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("unhoverd"));

	IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(ownerActor);

	if (InvenInterface)
	{
		UInventoryComponent* Inventory = InvenInterface->GetInventoryComponent();
		if (Inventory)
		{
			Inventory->SetItemInfo(-1);
		}
	}
}

FReply UInventorySlot::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result =  Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("mouse move"));


	return result;
}

void UInventorySlot::Init()
{
	UpdateSlot();
}

void UInventorySlot::UpdateSlot()
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
					if (itemList[slotIndex]->itemBase->stackCount > 1)
					{
						count->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
						count->SetText(FText::FromString(FString::FromInt(itemList[slotIndex]->itemBase->stackCount)));
					}
					else
					{

						count->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
					}

				}
				else
				{
					icon->SetBrushFromTexture(nullptr);
					icon->SetBrushTintColor(FLinearColor(1.f, 1.f, 1.f, 0.f));
					count->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
				}
			}
		}
	}

}

void UInventorySlot::DragSlotColor(FLinearColor Color)
{
	slotBackGround->SetBrushTintColor(Color);
}
