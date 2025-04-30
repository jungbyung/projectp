// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffWidget.h"
#include "BuffSlot.h"
#include "../../Item/ItemBase.h"
#include "../../Item/InventoryItem.h"
#include "../../Player/Inventory/InventoryComponent.h"
#include "../../Player/Inventory/InventoryInterface.h"


void UBuffWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	buffList = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("BuffList")));


}

void UBuffWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
}

void UBuffWidget::AddBuff(UItemBase* ItemBase)
{

	int32 Index = -1;
	for (int32 i = 0; i < buffList->GetChildrenCount(); ++i)
	{
		UBuffSlot* bs =  Cast<UBuffSlot>(buffList->GetChildAt(i));

		if (bs->GetBuffName() == ItemBase->itemName)
		{
			Index = i;
			bs->NotUse();

			break;
		}
	}

	if (Index != -1)
	{
		buffList->RemoveChildAt(Index);

		IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

		if (inventoryInterface)
		{
			UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

			if (inventory)
			{
				inventory->RemoveBuffItem(Index);
				
			}
		}
	}

	UBuffSlot* BuffSlot = WidgetTree->ConstructWidget<UBuffSlot>(buffSlotClass);
	
//	UBuffSlot* BuffSlot = NewObject<UBuffSlot>(GetWorld(), buffSlotClass); 

	//UBuffSlot* BuffSlot = NewObject<UBuffSlot>(GetWorld(),
	//	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/WB_BuffSlot.WB_BuffSlot_C'"));

	if (IsValid(BuffSlot))
	{
		buffList->AddChild(BuffSlot);

		BuffSlot->SetIcon(ItemBase->icon);
		BuffSlot->SetBuffName(ItemBase->itemName);
		BuffSlot->SetDuration(0.f);
		BuffSlot->SetDurationTime(ItemBase->options[0].duration);
		BuffSlot->Use();
		BuffSlot->BuffListDelegate.AddUObject(this, &UBuffWidget::RemoveBuffList);

		IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

		if (inventoryInterface)
		{
			UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

			if (inventory)
			{
				UInventoryItem* buffItem = inventory->GetBuffItemLast();
				if (buffItem)
				{
					buffItem->SetBuffSlot(BuffSlot);
				}
			}
		}

		UHorizontalBoxSlot* HorizontalBoxSlot = Cast<UHorizontalBoxSlot>(BuffSlot->Slot);

		HorizontalBoxSlot->SetSize(ESlateSizeRule::Automatic);
		HorizontalBoxSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
		HorizontalBoxSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("create buff"));
	}

}

void UBuffWidget::RemoveBuffList(UBuffSlot* BuffSlot)
{
	buffList->RemoveChild(BuffSlot);
}
