// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemDataAsset.h"
#include "ItemPotionData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemPotionData : public UItemDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(TEXT("ItemDataAsset"), GetFName());
	}
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FItemOption> options;

public:
	virtual TArray<FItemOption> GetItemOption() { return options; }
	virtual void SetItemOption(TArray<FItemOption> Options) { options = Options; }

};
