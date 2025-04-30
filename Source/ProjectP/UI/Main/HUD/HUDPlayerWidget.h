// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseUserWidget.h"
#include "HUDPlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UHUDPlayerWidget : public UBaseUserWidget
{
	GENERATED_BODY()

protected:

	TObjectPtr<UProgressBar> hpBar;
	TObjectPtr<UProgressBar> stamina;
	TObjectPtr<UProgressBar> mpBar;
	//TObjectPtr<UImage> renderTarget;

protected:
	virtual void NativeOnInitialized();

public:
	void SetRenderTarget(UTexture2D* Texture);
	void SetHPRatio(float HPRatio);
	void SetStaminaRatio(float StaminaRatio);

};
