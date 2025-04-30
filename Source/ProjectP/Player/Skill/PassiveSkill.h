// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "PassiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPassiveSkill : public USkillBase
{
	GENERATED_BODY()

public:
	UPassiveSkill();

public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
