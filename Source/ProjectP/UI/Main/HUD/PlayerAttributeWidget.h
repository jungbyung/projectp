// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../..//BaseUserWidget.h"
#include "PlayerAttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerAttributeWidget : public UBaseUserWidget
{
	GENERATED_BODY()
protected:


	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton>		titleBar;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton>		closeButton;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> job;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> hp;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> stemina;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> attackPower;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> defense;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> attackSpeed;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> moveSpeed;

protected:
	virtual void NativeOnInitialized();
public:

	void Init(FPlayerStateData Attribute);

	UFUNCTION()
	void CloseButtonClick();
	
	UFUNCTION()
	void TitleBarDown();

	UFUNCTION()
	void TitleBarUp();


	void SetAttributeJob(const FString& Job);
	void SetAttributeHP(int32 HP, int32 HPMax);
	void SetAttributeHP(float HPRatio);
	void SetAttributeStemina(int32 Stemina, int32 SteminaMax);
	void SetAttributeStemina(float SteminaRatio);
	void SetAttributeAttackPower(int32 AttackPower);
	void SetAttributeDefense(int32 Defense);
	void SetAttributeAttackSpeed(float AttackSpeed);
	void SetAttributeMoveSpeed(float MoveSpeed);
};
