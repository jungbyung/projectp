// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultuicommon.h"
#include "Blueprint/UserWidget.h"
#include "BuffSlot.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBuffList, class UBuffSlot*);

/**
 * 
 */
UCLASS()
class PROJECTP_API UBuffSlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	FString buffName;
	TObjectPtr<UImage> icon;
	TObjectPtr<UProgressBar> duration;

	float durationTimeMax = 0.f;
	float durationTime = 0.f;

	bool isUse = false;

public:
	FOnBuffList BuffListDelegate;
protected:
	virtual void NativeOnInitialized();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetBuffName(const FString& BuffName) { buffName = BuffName; }
	void SetIcon(UTexture2D* Icon);
	//void SetDurationRatio(float DurationRatio);
	void SetDuration(float DurationRatio);
	void SetDurationTime(float DurationTime) { durationTimeMax = DurationTime; }
	void Use();
	void NotUse();

	FString GetBuffName() { return buffName; }

};
