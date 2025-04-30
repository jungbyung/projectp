// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ADefaultPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class UMainWidget> mainWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UMainWidget> mainWidget;
public:
	class UMainWidget* GetMainWidget() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;

public:
	void SetPlayerRenderTarget(UTexture2D* Texture);
	void SetHPRatio(float HPRatio);
	void SetStaminaRatio(float StaminaRatio);
	void SetSkillCoolTime(int32 Index, float Ratio);
	void SkillCoolTimeEnd(int32 Index);
	void SetItemInfo(class UItemBase* ItemBase, bool Visible);
	void SetSkillInfo(class USkillBase* Skill, bool Visible);
	void ShowMouseCursor();

	void ToggleInventory();
	void ToggleAttribute();

	void AddBuffItem(class UItemBase* Data);

	void InitAttribute();
	void SetAttributeJob(const FString& Job);
	void SetAttributeHP(int32 HP, int32 HPMax);
	void SetAttributeStemina(int32 Stemina, int32 SteminaMax);
	void SetAttributeAttackPower(int32 AttackPower);
	void SetAttributeDefense(int32 Defense);
	void SetAttributeAttackSpeed(float AttackSpeed);
	void SetAttributeMoveSpeed(float MoveSpeed);
};
