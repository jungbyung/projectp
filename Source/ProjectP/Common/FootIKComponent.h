// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "Components/ActorComponent.h"
#include "FootIKComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UFootIKComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFootIKComponent();
protected:
	APawn* ownerPawn = nullptr;
	USkeletalMeshComponent* ownerMesh = nullptr;

	float ownerOffset = 0.f;

	FFootIKResult footIKLeft;
	FFootIKResult footIKRight;

	FRotator footRotLeft;
	FRotator footRotRight;

	FName footSocketLeftName = TEXT("Foot_L");
	FName footSocketRightName = TEXT("Foot_R");

	float capsuleHalfHeight;

	float hipOffset;
	float footOffsetLeft;
	float footOffsetRight;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void TraceFloor(FFootIKResult& Result, float TraceDist, const FName& SocketName);
	void UpdateCapsule(float DeltaTime, float Hip, bool Reset);
	FRotator ComputeRotator(FVector NormalVector);
	FRotator FootRotation(float DeltaTime, const FRotator& TargetRot, const FRotator& FootRot, float RotSpeed);
	float FootOffset(float DeltaTime, float Target, float Current, float Speed);

public:
	void SetOwner(APawn* Pawn, USkeletalMeshComponent* Mesh);
	void SetOwnerOffset(float Offset);
};
