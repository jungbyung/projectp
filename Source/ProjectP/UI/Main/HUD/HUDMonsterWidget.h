// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../BaseUserWidget.h"
#include "HUDMonsterWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UHUDMonsterWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:
	TObjectPtr<UProgressBar> hpBar;
	TObjectPtr<UTextBlock> name;

protected:
	virtual void NativeOnInitialized();

public:
	void SetHPRatio(float HPRatio);
	void SetName(const FString& Name);
};
