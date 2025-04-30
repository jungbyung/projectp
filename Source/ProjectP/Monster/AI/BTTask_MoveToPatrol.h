// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToPatrol.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UBTTask_MoveToPatrol : public UBTTask_MoveTo
{
	GENERATED_BODY()
public:
	UBTTask_MoveToPatrol();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
	
};
