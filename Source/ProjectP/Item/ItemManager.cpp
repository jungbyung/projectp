#include "ItemManager.h"
#include "PotionItem.h"

void CItemManager::Init()
{
	AddItemTable<UPotionItem>(TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_PotionData.DT_PotionData'"));
	

}


template<typename T>
inline void CItemManager::AddItemTable(const FString& Path)
{

	UDataTable* DataTable = LoadObject<UDataTable>(nullptr, *Path);

	if (DataTable)
	{
		TArray<FItemBaseData*> BaseDatas;
		DataTable->GetAllRows<FItemBaseData>(TEXT(""), BaseDatas);

		for (FItemBaseData* BaseData : BaseDatas)
		{
			T* NewItem = NewObject<T>(T::StaticClass());
			NewItem->type = BaseData->type;
			NewItem->typeName = BaseData->typeName;
			NewItem->itemName = BaseData->itemName;
			NewItem->desc = BaseData->desc;
			NewItem->icon = BaseData->icon;
			NewItem->buyPrice = BaseData->buyPrice;
			NewItem->sellPrice = BaseData->sellPrice;
			NewItem->stackCount = BaseData->stackCount;
			NewItem->maxStackCount = BaseData->maxStackCount;
			NewItem->options = BaseData->options;
			NewItem->SetNiagara( BaseData->niagara);

			AddItemTable(NewItem);

		}
	}
}

void CItemManager::AddItemTable(const FString& ItemType, const FString& Path)
{

//	itemTableMap.Add(ItemType, NewItemBase<UItemBase>(Path));
}

void CItemManager::AddItemTable(UItemBase* ItemBase)
{
	itemTableMap.Add(ItemBase->typeName, ItemBase);
}

UItemBase* CItemManager::GetItem(const FString& ItemName)
{
	return itemTableMap.FindRef(ItemName);
}
