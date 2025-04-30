// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "UObject/NoExportTypes.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UInputData : public UObject
{
	GENERATED_BODY()
public:
	UInputData();

public:

	UInputMappingContext* context = nullptr;

	UInputAction* move = nullptr;
	UInputAction* attack = nullptr;
	UInputAction* skillActive1 = nullptr;
	UInputAction* skillActive2 = nullptr;
	UInputAction* skillActive3 = nullptr;
	UInputAction* skillActive4 = nullptr;
	UInputAction* rotation = nullptr;
	UInputAction* inventoryWidget = nullptr;
	UInputAction* skillWidget = nullptr;
	UInputAction* statusWidget = nullptr;
	UInputAction* itemAction = nullptr;
	UInputAction* run = nullptr;
	UInputAction* dodge = nullptr;
	UInputAction* useQuickItem = nullptr;
	UInputAction* block = nullptr;
	
};
