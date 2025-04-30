// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "ActiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UActiveSkill : public USkillBase
{
	GENERATED_BODY()

public:
	UActiveSkill();

public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
