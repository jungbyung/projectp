#pragma once

#include "Engine.h"

#include "iteminfo.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Potion,
	Equipment,
	Other
};
UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	Weapon,
	Armor
};

UENUM(BlueprintType)
enum class EPotionType : uint8
{
	AttackPowerUp,
	DefenseUp,
	HPRecovery,
	StaminaRecovery,
	MoveSpeedUp,
	AttackSpeedUp
};
UENUM(BlueprintType)
enum class EItemOption : uint8
{
	AttackPowerUp,
	DefenseUp,
	HPRecovery,
	HPMaxUp,
	StaminaRecovery,
	StaminaMaxUp,
	MoveSpeedUp,
	AttackSpeedUp
};


USTRUCT(BlueprintType)
struct FItemOption : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemOption option;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float increase;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float duration;
};

FString GetItemOptionString(EItemOption Option);

USTRUCT(BlueprintType)
struct FItemBaseData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString typeName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 buyPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 sellPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 stackCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 maxStackCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemOption> options;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UNiagaraSystem>> niagara;
	
};

USTRUCT(BlueprintType)
struct FWeaponItemData : public FItemBaseData
{
	GENERATED_USTRUCT_BODY()
};


USTRUCT(BlueprintType)
struct FPotionItemData : public FItemBaseData
{
	GENERATED_USTRUCT_BODY()
};