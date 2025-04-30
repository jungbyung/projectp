// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDPlayerWidget.h"

void UHUDPlayerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	//mpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBar")));
	stamina = Cast<UProgressBar>(GetWidgetFromName(TEXT("Stamina")));

	//renderTarget = Cast<UImage>(GetWidgetFromName(TEXT("Character")));


}

void UHUDPlayerWidget::SetRenderTarget(UTexture2D* Texture)
{
//	renderTarget->SetBrushFromTexture(Texture);
}

void UHUDPlayerWidget::SetHPRatio(float HPRatio)
{
	hpBar->SetPercent(HPRatio);
}

void UHUDPlayerWidget::SetStaminaRatio(float StaminaRatio)
{
	stamina->SetPercent(StaminaRatio);
}
