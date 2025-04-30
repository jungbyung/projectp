// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"
#include "DefaultGameState.h"
#include "../Player/DefaultPlayerController.h"
#include "../Player/DefaultPlayerState.h"
#include "../Player/PlayerCharacter.h"
#include "../player/shinobiCharacter.h"
#include "../item/ItemManager.h"

ADefaultGameMode::ADefaultGameMode()
{
	CItemManager::GetInstance()->Init();


	DefaultPawnClass = AShinobiCharacter::StaticClass();
	GameStateClass = ADefaultGameState::StaticClass();
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();

	playerJob = EPlayerJob::Shinobi;

}

FName ADefaultGameMode::GetPlayerJobName()
{
	return TEXT("Shinobi");
}
