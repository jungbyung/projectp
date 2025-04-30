// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "../../../Player/DefaultPlayerController.h"
#include "../../../player/Inventory/InventoryInterface.h"
#include "../../../player/inventory/inventorycomponent.h"
#include "../MainWidget.h"
#include "QuickItemSlot.h"

void UItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	quickItem = Cast<UQuickItemSlot>(GetWidgetFromName(TEXT("WB_QuickItemSlot")));
	

	
}

void UItemSlotWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

void UItemSlotWidget::Init()
{
	quickItem->SetOwnerActor(ownerActor);

	IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

	if (inventoryInterface)
	{
		UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

		if (inventory)
		{
			inventory->quickItemSetDelegate.AddUObject(this, &UItemSlotWidget::SetQuickItem);
			inventory->useQuickItemDelegate.AddUObject(this, &UItemSlotWidget::UseQuickItem);
		}
	}
}

void UItemSlotWidget::SetQuickItem(int32 Index)
{
	quickItem->SetSlotIndex(Index);
	quickItem->SetQuickSlot(Index);
}

void UItemSlotWidget::UseQuickItem()
{
	quickItem->UpdateSlot();
}
