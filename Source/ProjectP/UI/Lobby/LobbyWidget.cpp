// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyWidget.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& ObjectInitializer)
	: UBaseUserWidget(ObjectInitializer)

{
}

void ULobbyWidget::NativeOnInitialized()
{
	gameStart = Cast<UButton>(GetWidgetFromName(TEXT("GameStartButton")));
	gameStartText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GameStartText")));

	testLevel = Cast<UButton>(GetWidgetFromName(TEXT("TestLevel")));

	testLevel->OnClicked.AddDynamic(this, &ULobbyWidget::GameTestLevel);

	gameStart->OnClicked.AddDynamic(this, &ULobbyWidget::GameStart);
	gameStart->OnHovered.AddDynamic(this, &ULobbyWidget::GameStartHovered);
	gameStart->OnUnhovered.AddDynamic(this, &ULobbyWidget::GameStartUnHovered);
}

void ULobbyWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void ULobbyWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULobbyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULobbyWidget::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainLevel"));

}

void ULobbyWidget::GameStartHovered()
{
	gameStartText->SetColorAndOpacity(FLinearColor(1.0f, 0.2f, 0.2f, 1.f));
}

void ULobbyWidget::GameStartUnHovered()
{
	gameStartText->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.f));
}

void ULobbyWidget::GameTestLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("TestLevel"));

}
