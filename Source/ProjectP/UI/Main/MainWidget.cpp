// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "HUD/HUDPlayerWidget.h"
#include "HUD/PlayerSkillWidget.h"
#include "HUD/InventoryWidget.h"
#include "HUD/ItemInfoWidget.h"
#include "hud/ItemSlotWidget.h"
#include "HUD/PlayerAttributeWidget.h"
#include "buffwidget.h"
#include "hud/HUDMonsterWidget.h"
#include "../../Item/ItemBase.h"

UMainWidget::UMainWidget(const FObjectInitializer& ObjectInitializer)
	:UBaseUserWidget(ObjectInitializer)
{
}

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	playerHUD = Cast<UHUDPlayerWidget>(GetWidgetFromName(TEXT("WB_PlayerHUD")));
	skillWidget = Cast<UPlayerSkillWidget>(GetWidgetFromName(TEXT("WB_PlayerSkillWidget")));
	inventoryWidget = Cast<UInventoryWidget>(GetWidgetFromName(TEXT("WB_InventoryWidget")));
	itemQuickWidget = Cast<UItemSlotWidget>(GetWidgetFromName(TEXT("WB_ItemSlotWidget")));
	itemInfoWidget = Cast<UItemInfoWidget>(GetWidgetFromName(TEXT("WB_ItemInfoWidget")));
	attributeWidget = Cast<UPlayerAttributeWidget>(GetWidgetFromName(TEXT("WB_AttributeWidget")));
	buffWidget = Cast<UBuffWidget>(GetWidgetFromName(TEXT("WB_BuffWidget")));
	monsterHUD = Cast<UHUDMonsterWidget>(GetWidgetFromName(TEXT("WB_MonsterHUD")));
}

void UMainWidget::NativePreConstruct()
{
}

void UMainWidget::NativeConstruct()
{
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
}

FReply UMainWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply result = Super::NativeOnMouseMove(InGeometry, InMouseEvent);


	if (itemInfoWidget->Visibility == ESlateVisibility::Visible)
	{
		UCanvasPanelSlot* panelSlot = Cast<UCanvasPanelSlot>(itemInfoWidget->Slot);

		if (IsValid(panelSlot))
		{
			FVector2D mousePos = InMouseEvent.GetScreenSpacePosition();

			FVector2D widgetPos = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry, mousePos);
			FVector2D ViewPortSize = FVector2D(1920.f, 1080.f);

			UCanvasPanelSlot* mainSlot = Cast<UCanvasPanelSlot>(this->Slot);
			
			//GetWorld()->GetGameViewport()->GetViewportSize(ViewPortSize);

			FVector2D PanelSize =  panelSlot->GetSize();


			widgetPos += FVector2D(1.f, 1.f);

			FVector2D correct = widgetPos + PanelSize;

			if (correct.X > ViewPortSize.X)
			{
				widgetPos.X -= (PanelSize.X + 1.f);
			}
			if (correct.Y > ViewPortSize.Y)
			{
				widgetPos.Y -= (PanelSize.Y + 1.f);
			}
			panelSlot->SetPosition(widgetPos);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("mouse move"));
	return result;
}

void UMainWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	//SetItemInfo(nullptr, false);
}

void UMainWidget::SetHPRatio(float HPRatio)
{
	playerHUD->SetHPRatio(HPRatio);
}

void UMainWidget::SetStaminaRatio(float StaminaRatio)
{
	playerHUD->SetStaminaRatio(StaminaRatio);
}

void UMainWidget::SetInitialized(int32 HP, int32 MaxHP, int32 MP, int32 MaxMP)
{
}

void UMainWidget::SetPlayerRenderTarget(UTexture2D* Texture)
{
	playerHUD->SetRenderTarget(Texture);
}

void UMainWidget::SetSkillCoolTime(int32 Index, float Ratio)
{
	skillWidget->SetSkillCoolTime(Index, Ratio);
}

void UMainWidget::SetItemInfo(class UItemBase* ItemBase, bool Visible)
{
	if (Visible)
	{
		itemInfoWidget->SetVisibility(ESlateVisibility::Visible);
		itemInfoWidget->SetItem(ItemBase);

	}
	else
	{
		itemInfoWidget->SetVisibility(ESlateVisibility::Collapsed);

	}
}

void UMainWidget::SetSkillInfo(USkillBase* Skill, bool Visible)
{

	if (Visible)
	{
		itemInfoWidget->SetVisibility(ESlateVisibility::Visible);
		itemInfoWidget->SetSkill(Skill);

	}
	else
	{
		itemInfoWidget->SetVisibility(ESlateVisibility::Collapsed);

	}
}

void UMainWidget::SkillCoolTimeEnd(int32 Index)
{
	skillWidget->SkillCoolTimeEnd(Index);
}

void UMainWidget::SetMonsterHPRatio(float HPRatio)
{
	monsterHUD->SetHPRatio(HPRatio);
}

void UMainWidget::SetMonsterNameText(const FString& Name)
{
	monsterHUD->SetName(Name);
}

void UMainWidget::VisibleMonsterHPHUD(bool Visible)
{
	if (monsterHUD)
	{
		if (Visible)
			monsterHUD->SetVisibility(ESlateVisibility::Visible);
		else
			monsterHUD->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidget::SetWidgetOwnerActor(AActor* Actor)
{
	inventoryWidget->SetOwnerActor(Actor);
	itemQuickWidget->SetOwnerActor(Actor);
	skillWidget->SetOwnerActor(Actor);
	attributeWidget->SetOwnerActor(Actor);
	buffWidget->SetOwnerActor(Actor);
}

void UMainWidget::InitWidget()
{
	inventoryWidget->Init();
	itemQuickWidget->Init();
	skillWidget->Init();

}

void UMainWidget::SetInventoryOwnerActor(AActor* Actor)
{
	inventoryWidget->SetOwnerActor(Actor);
	itemQuickWidget->SetOwnerActor(Actor);
	skillWidget->SetOwnerActor(Actor);
}

void UMainWidget::InitInventory()
{
	inventoryWidget->Init();
	itemQuickWidget->Init();
	skillWidget->Init();
}

void UMainWidget::InitAttribute(FPlayerStateData Attribute)
{
	attributeWidget->Init(Attribute);
}

void UMainWidget::ToggleInventory()
{
	isInventory = !isInventory;
	if (isInventory)
		inventoryWidget->SetVisibility(ESlateVisibility::Visible);
	else
	{
		inventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
		itemInfoWidget->SetVisibility(ESlateVisibility::Collapsed);

	}

}

void UMainWidget::ToggleAttribute()
{
	isAttribute = !isAttribute;
	if (isAttribute)
		attributeWidget->SetVisibility(ESlateVisibility::Visible);
	else
	{
		attributeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMainWidget::AddBuffItem(UItemBase* Data)
{
	buffWidget->AddBuff(Data);
}

void UMainWidget::SetAttributeJob(const FString& Job)
{
	attributeWidget->SetAttributeJob(Job);
}

void UMainWidget::SetAttributeHP(int32 HP, int32 HPMax)
{
	attributeWidget->SetAttributeHP(HP, HPMax);
}

void UMainWidget::SetAttributeStemina(int32 Stemina, int32 SteminaMax)
{
	attributeWidget->SetAttributeStemina(Stemina, SteminaMax);
}

void UMainWidget::SetAttributeAttackPower(int32 AttackPower)
{
	attributeWidget->SetAttributeAttackPower(AttackPower);
}

void UMainWidget::SetAttributeDefense(int32 Defense)
{
	attributeWidget->SetAttributeDefense(Defense);
}

void UMainWidget::SetAttributeAttackSpeed(float AttackSpeed)
{
	attributeWidget->SetAttributeAttackSpeed(AttackSpeed);
}

void UMainWidget::SetAttributeMoveSpeed(float MoveSpeed)
{
	attributeWidget->SetAttributeMoveSpeed(MoveSpeed);
}
