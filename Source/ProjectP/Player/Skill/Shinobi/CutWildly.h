// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../ActiveSkill.h"
#include "CutWildly.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UCutWildly : public UActiveSkill
{
	GENERATED_BODY()
public:
	UCutWildly();
public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
