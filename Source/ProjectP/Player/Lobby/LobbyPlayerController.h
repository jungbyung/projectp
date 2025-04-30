// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALobbyPlayerController();

protected:
	TSubclassOf<class ULobbyWidget>	lobbyWidgetClass;
	TObjectPtr<class ULobbyWidget>	lobbyWidget;

protected:
	virtual void BeginPlay() override;
};
