// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UMainWidget : public UBaseUserWidget
{
	GENERATED_BODY()
public:
	UMainWidget(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UHUDPlayerWidget> playerHUD;

	TObjectPtr<class UPlayerSkillWidget> skillWidget;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UInventoryWidget> inventoryWidget;
	TObjectPtr<class UItemSlotWidget> itemQuickWidget;
	TObjectPtr<class UItemInfoWidget> itemInfoWidget;
	TObjectPtr<class UPlayerAttributeWidget> attributeWidget;
	TObjectPtr<class UBuffWidget> buffWidget;
	TObjectPtr<class UHUDMonsterWidget> monsterHUD;

	bool isInventory = false;
	bool isAttribute = false;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);


public:
	void SetHPRatio(float HPRatio);
	void SetStaminaRatio(float StaminaRatio);
	void SetInitialized(int32 HP, int32 MaxHP, int32 MP, int32 MaxMP);
	void SetPlayerRenderTarget(UTexture2D* Texture);
	void SetSkillCoolTime(int32 Index, float Ratio);
	void SetItemInfo(class UItemBase* ItemBase, bool Visible);
	void SetSkillInfo(class USkillBase* Skill, bool Visible);
	void SkillCoolTimeEnd(int32 Index);

	void SetMonsterHPRatio(float HPRatio);
	void SetMonsterNameText(const FString& Name);
	void VisibleMonsterHPHUD(bool Visible);

	void SetWidgetOwnerActor(AActor* Actor);
	void InitWidget();
	void SetInventoryOwnerActor(AActor* Actor);
	void InitInventory();
	void InitAttribute(FPlayerStateData Attribute);
	void ToggleInventory();
	void ToggleAttribute();
	void AddBuffItem(class UItemBase* ItemBase);

	bool IsInventory() { return isInventory; }
	bool IsAttribute() { return isAttribute; }


	void SetAttributeJob(const FString& Job);
	void SetAttributeHP(int32 HP, int32 HPMax);
	void SetAttributeStemina(int32 Stemina, int32 SteminaMax);
	void SetAttributeAttackPower(int32 AttackPower);
	void SetAttributeDefense(int32 Defense);
	void SetAttributeAttackSpeed(float AttackSpeed);
	void SetAttributeMoveSpeed(float MoveSpeed);
};
