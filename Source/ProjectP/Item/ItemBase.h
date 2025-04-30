// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemBase : public UObject
{
	GENERATED_BODY()
public:
	UItemBase();
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

public:
	virtual TArray<TObjectPtr<UNiagaraSystem>> GetNiagara() { return TArray<TObjectPtr<UNiagaraSystem>>(); }
	virtual void SetNiagara(TArray<TObjectPtr<UNiagaraSystem>> Niagara) {}

};
