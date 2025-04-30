// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMovementComponent.h"
#include "Monster.h"
#include "Animation/MonsterAnimInstance.h"

UMonsterMovementComponent::UMonsterMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMonsterMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMonsterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetPawnOwner() || !UpdatedComponent)
		return;

	FVector Location = UpdatedComponent->GetComponentLocation();

	UCapsuleComponent* Capsule = Cast<UCapsuleComponent>(UpdatedComponent);

	dodgeAccTime += DeltaTime;
	AMonster* Monster = Cast<AMonster>(GetPawnOwner());
	
	if (IsValid(Monster))
	{
		if (Monster->GetMonsterAnimInstance()->GetAnimState() == EMonsterAnimState::Dodge)
		{
			FVector dir = Monster->GetActorForwardVector();
			dir = dir.GetSafeNormal();
			velocity = dir * (dodgeDistance * maxSpeed) * DeltaTime;
			velocity.Z -= gravity * DeltaTime;
			velocity = velocity.GetClampedToMaxSize(maxSpeed);

		}
		else if (Monster->GetMonsterAnimInstance()->GetAnimState() == EMonsterAnimState::Run)
		{
			FVector dir = Monster->GetActorForwardVector();
			dir = dir.GetSafeNormal();
			velocity = dir * maxSpeed * DeltaTime;
			velocity.Z -= gravity * DeltaTime;
			velocity = velocity.GetClampedToMaxSize(maxSpeed);
		}
		else if (Monster->GetMonsterAnimInstance()->GetAnimState() == EMonsterAnimState::Idle)
		{
			velocity = FVector::Zero();
		}

		FHitResult	Hit;

		SafeMoveUpdatedComponent(velocity, UpdatedComponent->GetComponentRotation(),
			true, Hit);

		if (Hit.IsValidBlockingHit())
		{
			float HitDot = FVector::DotProduct(Hit.Normal, FVector::UpVector);

			//if(HitDot < 0.1)
			SlideAlongSurface(velocity, 1.f - Hit.Time, Hit.Normal,	Hit);
		}
		velocity = FVector::Zero();
	}

}
