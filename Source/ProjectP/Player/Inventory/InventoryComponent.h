// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryChange, class UInventoryItem*, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSetItemQuick, int32);
DECLARE_MULTICAST_DELEGATE(FOnUseItemQuick);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnInventoryHovered, const FGeometry&, const FPointerEvent&, int32);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UInventoryItem>> itemList;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<class UInventoryItem>> buffItemList;

	TObjectPtr<class UInventoryItem> quickItem;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 invenMaxCount;

	bool isHovered = false;
	bool isDrag = false;
public:
	FOnInventoryChange changeDelegate;
	FOnInventoryHovered hoveredDelegate;
	FOnSetItemQuick quickItemSetDelegate;
	FOnUseItemQuick useQuickItemDelegate;
public:
	TArray<TObjectPtr<class UInventoryItem>> GetItemList() { return itemList; }

	bool IsItemValid(int32 Index);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void InitializeComponent();
public:
	void InitInventory();
	void AddItem(const FString& Name);
	void UseItem(int32 Index);
	void UseQuickItem();
	void SwapItem(int32 PrevIndex, int32 ChangeIndex);
	void RemoveItem(int32 Index);
	void RemoveItem(class UInventoryItem* Item);
	bool ChangeItem(class UInventoryItem* Item, int32 Index);
	void HoveredItem(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, int32 Index);
	void SetQuickItem(int32 Index);
	void SetItemInfo(int32 Index);
	void SetDrag(bool Drag);
	bool GetDrag() { return isDrag; }

	UFUNCTION()
	void BuffItem(EItemOption ItemOption);

	TArray<TObjectPtr<class UInventoryItem>> GetBuffItemList();
	class UInventoryItem* GetBuffItemLast();
	class UInventoryItem* GetBuffItemAt(int32 Index);

	void RemoveBuffItem(int32 Index);
	void RemoveBuffItem(class UInventoryItem BuffItem);
		
};
