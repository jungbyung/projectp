// Fill out your copyright notice in the Description page of Project Settings.


#include "CutWildly.h"
#include "../../DefaultPlayerController.h"
#include "../../PlayerCharacter.h"
#include "../../animation/PlayerAnimInstance.h"

UCutWildly::UCutWildly()
{
}

void UCutWildly::Use()
{
	Super::Use();
}

void UCutWildly::UpdateCoolTime(float DeltaTime)
{
	Super::UpdateCoolTime(DeltaTime);
}

void UCutWildly::UpdateEnd()
{
	Super::UpdateEnd();
}
