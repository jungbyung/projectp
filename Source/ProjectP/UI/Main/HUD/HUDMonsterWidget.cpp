// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDMonsterWidget.h"

void UHUDMonsterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	name = Cast<UTextBlock>(GetWidgetFromName(TEXT("Name")));
}

void UHUDMonsterWidget::SetHPRatio(float HPRatio)
{
	hpBar->SetPercent(HPRatio);
}

void UHUDMonsterWidget::SetName(const FString& Name)
{
	name->SetText(FText::FromString(Name));
}
