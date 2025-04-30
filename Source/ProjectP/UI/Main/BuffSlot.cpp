// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffSlot.h"

void UBuffSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	icon = Cast<UImage>(GetWidgetFromName(TEXT("Icon")));
	duration = Cast<UProgressBar>(GetWidgetFromName(TEXT("Duration")));
}

void UBuffSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//if (isUse)
	//{
	//	durationTime += InDeltaTime;
	//	SetDuration(durationTime / durationTimeMax);
	//	if (durationTime > durationTimeMax)
	//	{
	//		isUse = false;
	//
	//		if (BuffListDelegate.IsBound())
	//			BuffListDelegate.Broadcast(this);
	//	}
	//}

}

void UBuffSlot::SetIcon(UTexture2D* Icon)
{
	if(IsValid(icon))
		icon->SetBrushFromTexture(Icon);
	else {
		icon = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
		icon->SetBrushFromTexture(Icon);
	}
}

void UBuffSlot::SetDuration(float DurationRatio)
{
	if(IsValid(duration))
		duration->SetPercent(DurationRatio);
	else
	{
		duration = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass());
		duration->SetPercent(DurationRatio);
	}
}

void UBuffSlot::Use()
{
	isUse = true;
}

void UBuffSlot::NotUse()
{
	isUse = false;
}
