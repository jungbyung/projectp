// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalRotation.h"


ADecalRotation::ADecalRotation()
{
	rotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("movement"));
	rotMovement->SetUpdatedComponent(root);

	rotMovement->RotationRate.Pitch = 0.f;
	rotMovement->RotationRate.Roll = 180.f;
	rotMovement->RotationRate.Yaw = 0.f;

}
