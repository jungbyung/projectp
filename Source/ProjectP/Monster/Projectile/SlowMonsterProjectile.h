// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MonsterProjectile.h"
#include "SlowMonsterProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ASlowMonsterProjectile : public AMonsterProjectile
{
	GENERATED_BODY()
public:
	ASlowMonsterProjectile();
protected:
	virtual void BeginPlay() override;
	

public:
	virtual void SetDecal();
};
