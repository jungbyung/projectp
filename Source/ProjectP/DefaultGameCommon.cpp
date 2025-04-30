// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameCommon.h"

DEFINE_LOG_CATEGORY(ProjectP);

FRotator GetTargetRotator(const FVector& Start, const FVector& Target)
{
    return UKismetMathLibrary::FindLookAtRotation(Start, Target);
}

FString GetItemOptionString(EItemOption Option)
{
    return FString();
}

const FString GetPlayerJobString(EPlayerJob Job)
{
    
	switch (Job)
	{
	case EPlayerJob::None:
		break;
	case EPlayerJob::Shinobi:
		return TEXT("Shinobi");
		break;
	default:
		break;
	}

	return TEXT("");



}
