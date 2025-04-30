// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BaseUserWidget.h"
#include "LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ULobbyWidget : public UBaseUserWidget
{
	GENERATED_BODY()
public:
	ULobbyWidget(const FObjectInitializer& ObjectInitializer);
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> gameStart;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UButton> testLevel;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UTextBlock> gameStartText;
protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeDestruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UFUNCTION()
	void GameStart();

	UFUNCTION()
	void GameStartHovered();
	UFUNCTION()
	void GameStartUnHovered();

	UFUNCTION()
	void GameTestLevel();

};
