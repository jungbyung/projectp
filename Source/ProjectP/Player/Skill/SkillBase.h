// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API USkillBase : public UObject
{
	GENERATED_BODY()

public:

	USkillBase();

protected:
	class APawn* ownerPawn;
	FSkillOption skillOption;
	bool isActive = false;

	float skillCoolTime = 3.f;
	float skillCool = 0.f;
	int32 skillIndex = -1;

	int32 useStamina = 0;
public:
	bool GetActive() { return isActive; }

	void SetOwnerPawn(class APawn* Pawn){ ownerPawn = Pawn;	}
	void SetSkillIndex(int32 Index) { skillIndex = Index; }
	int32 GetSkillIndex() { return skillIndex; }

	void SetUseStamina(int32 Stamina) { useStamina = Stamina; }
	int32 GetUseStamina() { return useStamina; }

	void SetSkillCoolTime(float SkillCoolTime) { skillCoolTime = SkillCoolTime; }

	void SetSkillOption(FSkillOption SkillOption) { skillOption = SkillOption; }
	FSkillOption GetSkillOption() { return skillOption; }

public:
	virtual void Use();
	virtual void UpdateCoolTime(float DeltaTime);
	virtual void UpdateEnd();
};
