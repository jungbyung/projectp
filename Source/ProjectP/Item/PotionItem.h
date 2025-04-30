// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPotionItem : public UItemBase
{
	GENERATED_BODY()
public:
	UPotionItem();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UNiagaraSystem>> niagara;

public:
	virtual TArray<TObjectPtr<UNiagaraSystem>> GetNiagara() { return niagara; }
	virtual void SetNiagara(TArray<TObjectPtr<UNiagaraSystem>> Niagara) { niagara = Niagara; }

};
