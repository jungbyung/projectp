// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"
#include "ItemBase.h"
#include "../UI/Main/BuffSlot.h"

UInventoryItem::UInventoryItem()
{
}

void UInventoryItem::Update(float DeltaTime)
{

	if (isUse)
	{
		CurrentDuration += DeltaTime;
		if (buffSlot)
		{
			buffSlot->SetDuration(CurrentDuration / duration);
		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("use item %f"), CurrentDuration));
		if (CurrentDuration > duration)
		{
			isUse = false;
			if (buffSlot->BuffListDelegate.IsBound())
				buffSlot->BuffListDelegate.Broadcast(buffSlot);
			//if (buffDelegate.IsBound())
			//buffDelegate.Broadcast(buffIndex);
		}
	}

}

void UInventoryItem::UseItem()
{
	duration = itemBase->options[0].duration;
	CurrentDuration = 0.f;
	isUse = true; 
}


void UInventoryItem::SetItem(UItemBase* Item)
{
	itemBase->type = Item->type;
	itemBase->itemName = Item->itemName;
	itemBase->typeName = Item->typeName;
	itemBase->desc = Item->desc;
	itemBase->icon = Item->icon;
	itemBase->buyPrice = Item->buyPrice;
	itemBase->sellPrice = Item->sellPrice;
	itemBase->stackCount = Item->stackCount;
	itemBase->maxStackCount = Item->maxStackCount;
	itemBase->options = Item->options;
}


UItemBase* UInventoryItem::GetItem()
{
	return itemBase;
}

void UInventoryItem::SetBuffSlot(UBuffSlot* BuffSlot)
{
	buffSlot = BuffSlot;
}
