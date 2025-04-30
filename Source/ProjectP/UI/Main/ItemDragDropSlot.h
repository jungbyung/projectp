// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UItemDragDropSlot : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	int32 prevSlotIndex = 0;
};
