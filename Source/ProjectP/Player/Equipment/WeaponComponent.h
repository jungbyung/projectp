// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../defaultgamecommon.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:
	UWeaponComponent();

protected:
public:

	void UpdateGuard(EGuardState GuardState);
};
