// Fill out your copyright notice in the Description page of Project Settings.


#include "FootIKComponent.h"
#include "CharacterInterface.h"

// Sets default values for this component's properties
UFootIKComponent::UFootIKComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFootIKComponent::BeginPlay()
{
	Super::BeginPlay();

	ICharacterInterface* CharacterInterface = Cast<ICharacterInterface>(ownerPawn);

	if (CharacterInterface)
		capsuleHalfHeight = CharacterInterface->GetRootCapsuleHalfHeight();

	if (ownerMesh)
	{
		footRotRight = FRotator::ZeroRotator;
		footRotLeft = FRotator::ZeroRotator;
		
	}
	
}


// Called every frame
void UFootIKComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceFloor(footIKLeft, 50.f, footSocketLeftName);
	TraceFloor(footIKRight, 50.f, footSocketRightName);

	FRotator targetL = ComputeRotator(footIKLeft.hitNormal);
	FRotator targetR = ComputeRotator(footIKRight.hitNormal);

	footRotLeft = FootRotation(DeltaTime, targetL, footRotLeft, 10.f);
	footRotRight = FootRotation(DeltaTime, targetR, footRotRight, 10.f);

	float HipOffset = UKismetMathLibrary::Min(footIKLeft.offset, footIKRight.offset);

	if (HipOffset > 0.f) HipOffset = 0.f;

	hipOffset = FootOffset(DeltaTime, HipOffset, hipOffset, 10.f);

	UpdateCapsule(DeltaTime, HipOffset, false);


	footOffsetLeft = FootOffset(DeltaTime, footIKLeft.offset - HipOffset, footOffsetLeft, 10.f);
	footOffsetRight = FootOffset(DeltaTime, (footIKRight.offset - HipOffset) * -1.f, footOffsetRight, 10.f);

	ICharacterInterface* charInterface = Cast<ICharacterInterface>(ownerPawn);
	if (charInterface)
	{
		charInterface->SetFootIkInfo(footIKLeft, footIKRight);
		charInterface->SetFootRotation(footRotLeft, footRotRight);
		charInterface->SetHipOffset(hipOffset);
		charInterface->SetFootOffset(footOffsetLeft, footOffsetRight);
	}
}

void UFootIKComponent::TraceFloor(FFootIKResult& Result, float TraceDist, const FName& SocketName)
{
	if (!ownerMesh) return;

	ICharacterInterface* charInterface = Cast<ICharacterInterface>(ownerPawn);

	FVector SocketLoc = ownerMesh->GetSocketLocation(SocketName);

	FVector LineStart = FVector(SocketLoc.X, SocketLoc.Y, ownerPawn->GetActorLocation().Z);
	FVector LineEnd = FVector(LineStart.X, LineStart.Y, ownerPawn->GetActorLocation().Z - ownerOffset - TraceDist);

	FHitResult HitResult;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(ownerPawn);

	EDrawDebugTrace::Type DebugType = EDrawDebugTrace::None;

	DebugType = EDrawDebugTrace::ForOneFrame;

	bool Collision = UKismetSystemLibrary::LineTraceSingle(GetWorld(), LineStart, LineEnd, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
		true, ignoreActors, DebugType, HitResult, true);

	Result.hitPoint = HitResult.ImpactPoint;
	Result.hitNormal = HitResult.ImpactNormal;


	if (Collision)
	{
		float Length = (HitResult.ImpactPoint - HitResult.TraceEnd).Size();
		Result.offset = (Length - TraceDist) + 5.f;
	}
	else
	{
		Result.offset = 0.f;
	}

}

void UFootIKComponent::UpdateCapsule(float DeltaTime, float Hip, bool Reset)
{
	if (!ownerMesh) return;

	ICharacterInterface* charInterface = Cast<ICharacterInterface>(ownerPawn);

	if (!charInterface)
		return;

	float CapsuleHalfHeight = 0.f;
	if (Reset)
	{
		CapsuleHalfHeight = capsuleHalfHeight;

	}
	else
	{
		CapsuleHalfHeight = UKismetMathLibrary::Abs(Hip) * 0.5f;
		CapsuleHalfHeight = capsuleHalfHeight - CapsuleHalfHeight;
	}

	float ScaledHalfHeight = charInterface->GetRootCapsuleHalfHeight();
	float Result = UKismetMathLibrary::FInterpTo(ScaledHalfHeight, CapsuleHalfHeight, DeltaTime, 10.f);

	charInterface->SetRootCapsuleHalfHeight(Result);

}

FRotator UFootIKComponent::ComputeRotator(FVector NormalVector)
{
	float Angle1 = UKismetMathLibrary::DegAtan2(NormalVector.Y, NormalVector.Z);
	float Angle2 = UKismetMathLibrary::DegAtan2(NormalVector.X, NormalVector.Z);

	Angle2 *= -1.f;

	return FRotator(Angle2, 0.f, Angle1);
}

FRotator UFootIKComponent::FootRotation(float DeltaTime, const FRotator& TargetRot, const FRotator& FootRot, float RotSpeed)
{
	FRotator InterpRot = UKismetMathLibrary::RInterpTo(FootRot, TargetRot, DeltaTime, RotSpeed);

	return InterpRot;
}

float UFootIKComponent::FootOffset(float DeltaTime, float Target, float Current, float Speed)
{
	float Result = UKismetMathLibrary::FInterpTo(Current, Target, DeltaTime, Speed);

	return Result;
}

void UFootIKComponent::SetOwner(APawn* Pawn, USkeletalMeshComponent* Mesh)
{
	ownerPawn = Pawn;
	ownerMesh = Mesh;
}

void UFootIKComponent::SetOwnerOffset(float Offset)
{
	ownerOffset = Offset;
}

