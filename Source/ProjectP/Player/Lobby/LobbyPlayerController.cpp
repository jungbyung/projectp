// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "../../UI/Lobby/LobbyWidget.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	bShowMouseCursor = true;

	static ConstructorHelpers::FClassFinder<UUserWidget>
		LobbyWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Lobby/WB-LobbyWidget.WB-LobbyWidget_C'"));

	if (LobbyWidgetClass.Succeeded())
		lobbyWidgetClass = LobbyWidgetClass.Class;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(lobbyWidgetClass))
	{
		lobbyWidget = CreateWidget<ULobbyWidget>(GetWorld(),
			lobbyWidgetClass);

		if (IsValid(lobbyWidget))
			lobbyWidget->AddToViewport();
	}
}
