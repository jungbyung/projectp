// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../ActiveSkill.h"
#include "DanceWildly.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UDanceWildly : public UActiveSkill
{
	GENERATED_BODY()


public:
	UDanceWildly();

public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
