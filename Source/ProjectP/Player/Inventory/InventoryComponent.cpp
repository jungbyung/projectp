// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "../../Item/InventoryItem.h"
#include "../PlayerCharacter.h"
#include "../DefaultPlayerController.h"
#include "../DefaultPlayerState.h"
#include "../../item/ItemManager.h"
#include "../../item/itembase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	bWantsInitializeComponent = true;
	invenMaxCount = 25;

	itemList.Init(nullptr, invenMaxCount);
}


bool UInventoryComponent::IsItemValid(int32 Index)
{
	return IsValid(itemList[Index]);
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	for (int32 i = 0; i < buffItemList.Num(); ++i)
	{
		if (buffItemList[i] != nullptr)
		{
			buffItemList[i]->Update(DeltaTime);
			if (!buffItemList[i]->IsUse())
			{
				BuffItem(buffItemList[i]->GetItem()->options[0].option);
				buffItemList.RemoveAt(i);
				break;
			}
		}
	}
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInventoryComponent::InitInventory()
{
}


void UInventoryComponent::AddItem(const FString& Name)
{
	UInventoryItem* item = NewObject<UInventoryItem>();
	if (item)
	{
		UItemBase* NewItem = CItemManager::GetInstance()->GetItem(Name);
		if (NewItem)
			item->itemBase = NewItem;
		else
		{
			delete NewItem;
			return;
		}


		for (int32 i = 0; i < invenMaxCount; ++i)
		{
			if (IsValid(itemList[i]))
			{
				if (itemList[i]->itemBase->itemName == NewItem->itemName &&
					itemList[i]->itemBase->stackCount < itemList[i]->itemBase->maxStackCount)
				{
					itemList[i]->itemBase->stackCount += 1;

					if (changeDelegate.IsBound())
						changeDelegate.Broadcast(item, i);
					break;
				}
			}
			else if (!IsValid(itemList[i]))
			{
				itemList[i] = item;
				if (changeDelegate.IsBound())
					changeDelegate.Broadcast(item, i);
				break;
			}
		}
	}
}

void UInventoryComponent::UseItem(int32 Index)
{
	//useItemList.Add(itemList[Index]);
	if (itemList[Index])
	{
		TArray<FItemOption> options = itemList[Index]->itemBase->options;

		APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
			TEXT("/Script/Engine.SoundWave'/Game/Sound/3/085594_potion-35983.085594_potion-35983'"));

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, player->GetActorLocation(), player->GetActorRotation());

		//options[0].option
		switch (options[0].option)
		{
		case EItemOption::AttackPowerUp:
			
			buffItemList.Add(itemList[Index]);
			itemList[Index]->UseItem();
			player->AttackPowerUp(options[0].increase);
			player->AddBuff(itemList[Index]);
			//itemList[Index]->buffDelegate.AddUObject(this, &UInventoryComponent::BuffItem);
			itemList[Index]->SetBuffItemIndex(0);
			RemoveItem(Index);
			break;
		case EItemOption::DefenseUp:
			
			buffItemList.Add(itemList[Index]);
			itemList[Index]->UseItem();
			//buffItemList[1]->SetBuffSlot()
			player->DefenseUp(options[0].increase);
			player->AddBuff(itemList[Index]);
			//itemList[Index]->buffDelegate.AddUObject(this, &UInventoryComponent::BuffItem);
			itemList[Index]->SetBuffItemIndex(1);
			RemoveItem(Index);
			break;
		case EItemOption::HPRecovery:
			player->AddHP(options[0].increase);
			RemoveItem(Index);
			//inventory->GetUseItemList().RemoveAt(i);
			break;
		case EItemOption::HPMaxUp:
			break;
		case EItemOption::StaminaRecovery:
			player->AddStamina(options[0].increase);
			RemoveItem(Index);
			break;
		case EItemOption::StaminaMaxUp:
			break;
		case EItemOption::MoveSpeedUp:
			break;
		case EItemOption::AttackSpeedUp:
			break;
		default:
			break;
		}
	}
}

void UInventoryComponent::UseQuickItem()
{
	if (quickItem)
	{
		UseItem(quickItem->GetQuickItemIndex());
	}
}

void UInventoryComponent::SwapItem(int32 PrevIndex, int32 ChangeIndex)
{
	itemList.Swap(PrevIndex, ChangeIndex);
	SetQuickItem(ChangeIndex);
	if (changeDelegate.IsBound())
	{
		changeDelegate.Broadcast(itemList[PrevIndex], ChangeIndex);
		changeDelegate.Broadcast(itemList[ChangeIndex], PrevIndex);
	}
}

void UInventoryComponent::RemoveItem(int32 Index)
{
	itemList[Index]->itemBase->stackCount--;
	if (itemList[Index]->itemBase->stackCount > 0)
	{
		if (changeDelegate.IsBound())
			changeDelegate.Broadcast(itemList[Index], Index);
	}
	else
	{
		itemList[Index] = nullptr;
		if (changeDelegate.IsBound())
			changeDelegate.Broadcast(nullptr, Index);
	}
	if (useQuickItemDelegate.IsBound() && quickItem)
		useQuickItemDelegate.Broadcast();
}

void UInventoryComponent::RemoveItem(UInventoryItem* Item)
{
	int32 Index = itemList.Find(Item);

	if (Index != INDEX_NONE)
		RemoveItem(Index);
}

bool UInventoryComponent::ChangeItem(UInventoryItem* Item, int32 Index)
{
	return false;
}

void UInventoryComponent::HoveredItem(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, int32 Index)
{
}

void UInventoryComponent::SetQuickItem(int32 Index)
{
	//quickItem->SetItemData(itemList[Index]->itemData);
	quickItem = itemList[Index];
	quickItem->setQuickItemIndex(Index);
	if (changeDelegate.IsBound())
	{
		changeDelegate.Broadcast(itemList[Index], Index);
	}
	if (quickItemSetDelegate.IsBound())
		quickItemSetDelegate.Broadcast(Index);
}

void UInventoryComponent::SetItemInfo(int32 Index)
{

	ADefaultPlayerController* PlayerController = GetWorld()->GetFirstPlayerController<ADefaultPlayerController>();

	if (PlayerController)
	{
		if (Index < 0 || isDrag)
		{
			PlayerController->SetItemInfo(nullptr, false);

		}
		else if (itemList[Index])
		{
			PlayerController->SetItemInfo(itemList[Index]->GetItem(), true);
		}
		else
		{
			PlayerController->SetItemInfo(nullptr, false);

		}
	} 
}

void UInventoryComponent::SetDrag(bool Drag)
{
	isDrag = Drag;
	if (Drag)
	{

		ADefaultPlayerController* PlayerController = GetWorld()->GetFirstPlayerController<ADefaultPlayerController>();

		if (PlayerController)
		{
			PlayerController->SetItemInfo(nullptr, false);
		}
	}
}

void UInventoryComponent::BuffItem(EItemOption ItemOption)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(player))
	{
		switch (ItemOption)
		{
		case EItemOption::AttackPowerUp:
			player->AttackPowerUp(0);
			break;
		case EItemOption::DefenseUp:
			player->DefenseUp(0);
			break;
		case EItemOption::HPRecovery:
			break;
		case EItemOption::HPMaxUp:
			break;
		case EItemOption::StaminaRecovery:
			break;
		case EItemOption::StaminaMaxUp:
			break;
		case EItemOption::MoveSpeedUp:
			break;
		case EItemOption::AttackSpeedUp:
			break;
		default:
			break;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("delegate"));
//	buffItemList.Remove(buffItemList[Index]);
}

TArray<TObjectPtr<class UInventoryItem>> UInventoryComponent::GetBuffItemList()
{
	return buffItemList;
}

UInventoryItem* UInventoryComponent::GetBuffItemLast()
{
	if (buffItemList.Num() < 0) return nullptr;
	return buffItemList[buffItemList.Num()-1];
}

UInventoryItem* UInventoryComponent::GetBuffItemAt(int32 Index)
{
	if (Index < 0 || Index >= buffItemList.Num()) return nullptr;
	return buffItemList[Index];
}

void UInventoryComponent::RemoveBuffItem(int32 Index)
{
	if (Index < 0 || Index >= buffItemList.Num()) return;
	buffItemList.RemoveAt(Index);
}

void UInventoryComponent::RemoveBuffItem(UInventoryItem BuffItem)
{
	buffItemList.Remove(BuffItem);
}
