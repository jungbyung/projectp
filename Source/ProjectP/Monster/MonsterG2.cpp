// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterG2.h"
#include "ai/EpicMonsterAIController.h"
#include "animation/monsteraniminstance.h"

AMonsterG2::AMonsterG2()
{
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/QuangPhan/G2_Mercenaries/Meshes/Characters/Combines/SK_LP287_MercA.SK_LP287_MercA'"));

	if (skeletalMesh.Succeeded())
		mesh->SetSkeletalMeshAsset(skeletalMesh.Object);

	body->SetCapsuleHalfHeight(100.f);

	mesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	mesh->SetReceivesDecals(false);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_G2AnimInstance.ABP_G2AnimInstance_C'"));

	if (animClass.Succeeded())
		mesh->SetAnimInstanceClass(animClass.Class);

	stateComponent->SetMonsterRowName(TEXT("G2"));
	widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AIControllerClass = AEpicMonsterAIController::StaticClass();
	equipItem = CreateDefaultSubobject<UEquipmentItem>(TEXT("equiptment"));

	equipItem->LoadWeapon(TEXT("/Script/Engine.SkeletalMesh'/Game/QuangPhan/G2_Mercenaries/Meshes/Weapons/SK_Sword.SK_Sword'"));
	equipItem->Init(mesh, TEXT("Weapon_Socket_R"));
}

void AMonsterG2::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterG2::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterG2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterG2::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterG2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterG2::Attack()
{
	animInst->SetAnimState(EMonsterAnimState::Attack);
	
	if(!animInst->AttackPattern())
		animInst->AttackMontage();

}

void AMonsterG2::NormalAttack()
{
}

void AMonsterG2::NormalStaggerAttack()
{
	FHitResult HitResult;
	FVector start, end;
	FQuat rot;

	start = GetActorLocation() + GetActorForwardVector() * 50.f;
	end = start + GetActorForwardVector() * stateComponent->GetAttackDistance();

	FCollisionQueryParams param(NAME_None, false, this);

	bool collision = GetWorld()->SweepSingleByChannel(HitResult, start, end,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(50.f),
		param);


#if ENABLE_DRAW_DEBUG

	FColor color = collision ? FColor::Red : FColor::Green;

	FVector dir = end - start;
	dir.Normalize();

	FQuat quat = FQuat::FindBetweenNormals(FVector::UpVector, dir);

	DrawDebugCapsule(GetWorld(), (start + end) * 0.5f,
		stateComponent->GetAttackDistance() * 0.5f, 75.f, quat, color, false, 0.5f);


#endif

	if (collision)
	{

		FPointDamageEvent PointDamageEvent;
		PointDamageEvent.HitInfo = HitResult;
		PointDamageEvent.Damage = stateComponent->GetAttackPower();
		PointDamageEvent.DamageTypeClass = UNormalStunDamageType::StaticClass();

		float Dmg = HitResult.GetActor()->TakeDamage(stateComponent->GetAttackPower(),
			PointDamageEvent, GetController(), this);

		///Script/Engine.ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_Rampage_Enraged_Impact.P_Rampage_Enraged_Impact'

		UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
			TEXT("/Script/Engine.ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_Rampage_Enraged_Impact.P_Rampage_Enraged_Impact'"));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

		USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
			TEXT("/Script/Engine.SoundWave'/Game/Sound/3/fist-punch-or-kick-7171.fist-punch-or-kick-7171'"));

		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());


	}
}

void AMonsterG2::FrontDodgeThrust()
{
	FrontDodge();
	animInst->bIsFollowUpAttack = true;
	animInst->followUpAttackIndex = 1;
}

void AMonsterG2::FrontDodge()
{
	animInst->SetAnimState(EMonsterAnimState::Dodge);
	animInst->SetDodgeDirection(EDirection::Front);
	
}

void AMonsterG2::Thrust()
{
	animInst->AttackMontage(1);
}

void AMonsterG2::AttackPattern()
{
}
