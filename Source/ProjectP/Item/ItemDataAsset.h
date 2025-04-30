// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("ItemDataAsset"), GetFName());
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString itemName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText desc;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 count;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 countMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 buyPrice;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 sellPrice;
public:
	virtual TArray<FItemOption> GetItemOption() { return TArray<FItemOption>(); }
	virtual void SetItemOption(TArray<FItemOption> Options) {}
};
