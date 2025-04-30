// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventorySlot.h"
#include "../../../Player/DefaultPlayerController.h"
#include "../../../player/Inventory/InventoryInterface.h"
#include "../../../player/inventory/inventorycomponent.h"
#include "../MainWidget.h"

void UInventoryWidget::NativeOnInitialized()
{
	titleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	closeButton = Cast<UButton>(GetWidgetFromName(TEXT("Close")));

	closeButton->OnClicked.AddDynamic(this, &UInventoryWidget::CloseButtonClick);
	titleBar->OnPressed.AddDynamic(this, &UInventoryWidget::TitleBarDown);
	titleBar->OnReleased.AddDynamic(this, &UInventoryWidget::TitleBarUp);
}

void UInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::Init()
{
	slots.Init(nullptr, 25);

	for (int32 i = 0; i < 25; ++i)
	{
		FString WidgetName = TEXT("WB_InventorySlot_") + FString::FromInt(i);

		UInventorySlot* slot = Cast<UInventorySlot>(GetWidgetFromName(*WidgetName));

		slot->SetOwnerActor(ownerActor);
		slot->SetSlotIndex(i);
		slot->Init();

		slots[i] = slot;
	}

	IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(ownerActor);

	if (inventoryInterface)
	{
		UInventoryComponent* inventory = inventoryInterface->GetInventoryComponent();

		if (inventory)
		{
			inventory->changeDelegate.AddUObject(this, &UInventoryWidget::ChangeInventory);
			inventory->hoveredDelegate.AddUObject(this, &UInventoryWidget::HoveredItem);
		}
	}
}

void UInventoryWidget::UpdateSlots()
{
	for (const auto& slot : slots)
		slot->UpdateSlot();
}

void UInventoryWidget::CloseButtonClick()
{
	ADefaultPlayerController* playerController = Cast<ADefaultPlayerController>(GetWorld()->GetFirstPlayerController());
	playerController->ToggleInventory();
}

void UInventoryWidget::ChangeInventory(UInventoryItem* Item, int32 Index)
{
	slots[Index]->UpdateSlot();
}

void UInventoryWidget::HoveredItem(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, int32 Index)
{
}

void UInventoryWidget::TitleBarDown()
{
	dragEnable = true;

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot);

	if (IsValid(PanelSlot))
	{
		dragPrevPos = PanelSlot->GetPosition();
	}
	dragOffset = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
}

void UInventoryWidget::TitleBarUp()
{
	dragEnable = false;
}
