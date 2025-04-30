// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActiveSkill.h"
#include "RisingSlash.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API URisingSlash : public UActiveSkill
{
	GENERATED_BODY()
public:
	URisingSlash();
public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
