// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeWidget.h"
#include "../../../Player/DefaultPlayerController.h"

void UPlayerAttributeWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	titleBar = Cast<UButton>(GetWidgetFromName(TEXT("TitleBar")));
	closeButton = Cast<UButton>(GetWidgetFromName(TEXT("Close")));

	job = Cast<UTextBlock>(GetWidgetFromName(TEXT("Job")));
	hp = Cast<UTextBlock>(GetWidgetFromName(TEXT("HP")));
	stemina = Cast<UTextBlock>(GetWidgetFromName(TEXT("Stemina")));
	attackPower = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackPower")));
	defense = Cast<UTextBlock>(GetWidgetFromName(TEXT("Defense")));
	attackSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackSpeed")));
	moveSpeed = Cast<UTextBlock>(GetWidgetFromName(TEXT("MoveSpeed")));

	closeButton->OnClicked.AddDynamic(this, &UPlayerAttributeWidget::CloseButtonClick);
	titleBar->OnPressed.AddDynamic(this, &UPlayerAttributeWidget::TitleBarDown);
	titleBar->OnReleased.AddDynamic(this, &UPlayerAttributeWidget::TitleBarUp);

}


void UPlayerAttributeWidget::Init(FPlayerStateData Attribute)
{
	SetAttributeJob(GetPlayerJobString(Attribute.job));
	SetAttributeHP(Attribute.hp, Attribute.hp);
	SetAttributeStemina(Attribute.mp, Attribute.mp);
	SetAttributeAttackPower(Attribute.attackPower);
	SetAttributeDefense(Attribute.defense);
	SetAttributeAttackSpeed(Attribute.attackSpeed);
	SetAttributeMoveSpeed(Attribute.walkSpeed);

}

void UPlayerAttributeWidget::CloseButtonClick()
{
	ADefaultPlayerController* playerController = Cast<ADefaultPlayerController>(GetWorld()->GetFirstPlayerController());
	playerController->ToggleAttribute();
}

void UPlayerAttributeWidget::TitleBarDown()
{
	dragEnable = true;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("titlebardown"));
	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Slot);

	if (IsValid(PanelSlot))
	{
		dragPrevPos = PanelSlot->GetPosition();
	}
	dragOffset = UWidgetLayoutLibrary::GetMousePositionOnViewport(this);
}

void UPlayerAttributeWidget::TitleBarUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("titlebarup"));
	dragEnable = false;
}

void UPlayerAttributeWidget::SetAttributeJob(const FString& Job)
{
	job->SetText(FText::FromString(Job));
}

void UPlayerAttributeWidget::SetAttributeHP(int32 HP, int32 HPMax)
{
	FString str = FString::Printf(TEXT("%d/%d"), HP, HPMax);
	hp->SetText(FText::FromString(str));
}

void UPlayerAttributeWidget::SetAttributeHP(float HPRatio)
{

}

void UPlayerAttributeWidget::SetAttributeStemina(int32 Stemina, int32 SteminaMax)
{
	FString str = FString::Printf(TEXT("%d/%d"), Stemina, SteminaMax);
	stemina->SetText(FText::FromString(str));
}

void UPlayerAttributeWidget::SetAttributeStemina(float SteminaRatio)
{
}

void UPlayerAttributeWidget::SetAttributeAttackPower(int32 AttackPower)
{

	attackPower->SetText(FText::FromString(FString::FromInt(AttackPower)));
}

void UPlayerAttributeWidget::SetAttributeDefense(int32 Defense)
{
	defense->SetText(FText::FromString(FString::FromInt(Defense)));
}

void UPlayerAttributeWidget::SetAttributeAttackSpeed(float AttackSpeed)
{
	FString str = FString::Printf(TEXT("%.1f"), AttackSpeed);
	attackSpeed->SetText(FText::FromString(str));
}

void UPlayerAttributeWidget::SetAttributeMoveSpeed(float MoveSpeed)
{
	FString str = FString::Printf(TEXT("%.1f"), MoveSpeed);
	moveSpeed->SetText(FText::FromString(str));
}
