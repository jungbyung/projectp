#pragma once

#include "../DefaultGameCommon.h"


class PROJECTP_API CItemManager : 
	public Singleton<CItemManager>
{
public:
	CItemManager() { Init(); }
	~CItemManager() {}

protected:
	TMap<FString, TObjectPtr<class UItemBase>> itemTableMap;
protected:
//	bool FindItemTable(EItemType ItemType) { return itemTableMap.Find(ItemType); }
public:
	void Init();

	template<typename T>
	void AddItemTable(const FString& Path);
	void AddItemTable(const FString& ItemType, const FString& Path);
	void AddItemTable( UItemBase* ItemBase);


	template<typename T>
	T* GetItem(FString ItemName) { return Cast<T>(GetItem(ItemName)); }
	class UItemBase* GetItem(const FString& ItemName);



};