// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "../Player/Lobby/LobbyPlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = ALobbyPlayerController::StaticClass();
}
