// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Decal.h"
#include "DecalRotation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ADecalRotation : public ADecal
{
	GENERATED_BODY()

public:
	ADecalRotation();

protected:

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* rotMovement;

};
