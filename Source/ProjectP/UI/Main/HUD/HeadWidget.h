// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../BaseUserWidget.h"
#include "HeadWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UHeadWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:

	TObjectPtr<UTextBlock> name;
	TObjectPtr<UProgressBar> hpBar;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetName(FText Name);
	void SetHPRatio(float HPRatio);
};
