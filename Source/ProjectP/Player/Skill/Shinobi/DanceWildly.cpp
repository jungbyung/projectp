// Fill out your copyright notice in the Description page of Project Settings.


#include "DanceWildly.h"
#include "../../DefaultPlayerController.h"
#include "../../PlayerCharacter.h"
#include "../../animation/PlayerAnimInstance.h"

UDanceWildly::UDanceWildly()
{
}

void UDanceWildly::Use()
{
	Super::Use();
}

void UDanceWildly::UpdateCoolTime(float DeltaTime)
{
	Super::UpdateCoolTime(DeltaTime);
}

void UDanceWildly::UpdateEnd()
{
	Super::UpdateEnd();
}
