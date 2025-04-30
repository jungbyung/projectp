// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterMutant.h"
#include "Animation/MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"

AMonsterMutant::AMonsterMutant()
{
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Models/Monsters/Mutant/Mutant.Mutant'"));

	if (skeletalMesh.Succeeded())
		mesh->SetSkeletalMeshAsset(skeletalMesh.Object);

	body->SetCapsuleHalfHeight(80.f);
	body->SetCapsuleRadius(30.f);

	mesh->SetRelativeLocation(FVector(0.f, 0.f, -80.f));
	mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_MutantAnimInstance.ABP_MutantAnimInstance_C'"));

	if (animClass.Succeeded())
		mesh->SetAnimInstanceClass(animClass.Class);

	stateComponent->SetMonsterRowName(TEXT("Mutant"));
}

void AMonsterMutant::BeginPlay()
{
	Super::BeginPlay();

	//stateComponent->setname
}

void AMonsterMutant::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterMutant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterMutant::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterMutant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterMutant::NormalAttack()
{

	TArray<FHitResult> HitResults;
	FVector start, end;
	FQuat rot;

	start = GetActorLocation() + GetActorForwardVector() * 50.f;
	end = start + GetActorForwardVector() * stateComponent->GetAttackDistance();

	FCollisionQueryParams param(NAME_None, false, this);

	bool collision = GetWorld()->SweepMultiByChannel(HitResults, start, end,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.f),
		param);


#if ENABLE_DRAW_DEBUG

	FColor color = collision ? FColor::Red : FColor::Green;

	FVector dir = end - start;
	dir.Normalize();

	FQuat quat = FQuat::FindBetweenNormals(FVector::UpVector, dir);

	DrawDebugCapsule(GetWorld(), (start + end) * 0.5f,
		stateComponent->GetAttackDistance() * 0.5f, 50.f, quat, color, false, 0.5f);


#endif

	if (collision)
	{
		FDamageEvent DmgEvent;

		for (const FHitResult HitResult : HitResults)
		{
			float Dmg = HitResult.GetActor()->TakeDamage(stateComponent->GetAttackPower(),
				DmgEvent, GetController(), this);
		}
	}
}
