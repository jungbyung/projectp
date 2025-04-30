// Fill out your copyright notice in the Description page of Project Settings.


#include "HeadWidget.h"

void UHeadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	name = Cast<UTextBlock>(GetWidgetFromName(TEXT("NameText")));
	hpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));

	name->SetText(FText::FromString(TEXT("")));
}

void UHeadWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UHeadWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeadWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UHeadWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UHeadWidget::SetName(FText Name)
{
	name->SetText(Name);
}

void UHeadWidget::SetHPRatio(float HPRatio)
{
	hpBar->SetPercent(HPRatio);
}
