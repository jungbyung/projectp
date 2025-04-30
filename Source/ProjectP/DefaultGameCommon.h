// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "Engine/AssetManager.h"
#include "NiagaraSystem.h"
#include "niagaracomponent.h"
#include "Item/ItemInfo.h"
#include "Common/normaldamagetype.h"
#include "common/NormalStunDamageType.h"
 
#include "perception/aiperceptioncomponent.h"
#include "perception/AIPerceptionStimuliSourceComponent.h"
#include "perception/aiperceptionTypes.h"
#include "perception/AISenseConfig_Sight.h"
#include "perception/aisenseconfig_hearing.h"
#include "perception/aisenseconfig_damage.h"

#include "behaviortree/behaviortree.h"
#include "behaviortree/blackboardData.h"
#include "behaviortree/blackboardcomponent.h"
#include "DefaultGameCommon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ProjectP, Warning, All);

FRotator GetTargetRotator(const FVector& Start, const FVector& Target);

template <typename T>
class Singleton
{
protected:
	Singleton() {}
	virtual ~Singleton() {}
private:
	static T* instance;
public:
	static T* GetInstance()
	{
		if (!instance)
			instance = new T;
		return instance;
	}
	static void DestroyInstance()
	{
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T> T* Singleton<T>::instance = nullptr;



USTRUCT(BlueprintType)
struct FFootIKResult
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)

	float offset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector hitPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector hitNormal;

};

UENUM(BlueprintType)
enum class EWalkDirection : uint8
{
	Forward,
	Back,
	Left,
	Right,
	ForwardRight,
	ForwardLeft,
	BackRight,
	BackLeft
};

UENUM(BlueprintType)
enum class EDirection : uint8
{
	None,
	Front,
	Back,
	Left,
	Right,
};


USTRUCT(BlueprintType)
struct FPlayerAnimData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> locomotionMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> animMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> attackSectionNameArray;

};

USTRUCT(BlueprintType)
struct FMonsterAnimData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> animMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> attackSectionNameArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> rangedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> rangedSectionNameArray;
};

UENUM(BlueprintType)
enum class EPlayerAnimState : uint8
{
	Locomotion,
	Dodge,
	Dead,
	Skill,
	Block,
	BlockCounter,
	Attack,
	NormalStagger
}; 

UENUM(BlueprintType)
enum class EBlock : uint8
{
	In,
	Out,
	Hit,
	Loop
};
UENUM(BlueprintType)
enum class EMonsterGrade : uint8
{
	Normal,
	Epic,
	Boss
};

UENUM(BlueprintType)
enum class EMonsterAnimState : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Ranged,
	Skill,
	Dodge,
	Hit
};

UENUM(BlueprintType)
enum class EPlayerJob : uint8
{
	None,
	Shinobi
};

UENUM(BlueprintType)
enum class EGuardState : uint8
{
	None,
	Parry,
	Block
};

USTRUCT(BlueprintType)
struct FMonsterStateData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EMonsterGrade grade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 defense;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 exp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 gold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float walkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float runSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float criticalHitChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float criticalHitRate;
};

USTRUCT(BlueprintType)
struct FPlayerStateData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerJob job;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 mp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 defense;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float walkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float runSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float criticalHitChance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float criticalHitRate;
};

USTRUCT(BlueprintType)
struct FSkillOption
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString skillName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 stamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float coolTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 attackCount;
};

USTRUCT(BlueprintType)
struct FPlayerSkillData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSkillOption> skillOptions;
};


const FString GetPlayerJobString(EPlayerJob Job);