// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefaultGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ADefaultGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADefaultGameState();
protected:
	bool isPlayerLive = true;

public:
	bool IsPlayerLive() { return isPlayerLive; }
	void PlayerLive(bool Live) { isPlayerLive = Live; }
	
};
