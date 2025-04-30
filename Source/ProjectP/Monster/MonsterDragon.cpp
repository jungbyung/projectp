// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterDragon.h"
#include "Animation/MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"
#include "Projectile/MonsterProjectile.h"
#include "projectile/SlowMonsterProjectile.h"
#include "Skill/RangedSkill.h"

AMonsterDragon::AMonsterDragon()
{
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON'"));

	if (skeletalMesh.Succeeded())
		mesh->SetSkeletalMeshAsset(skeletalMesh.Object);

	body->SetCapsuleHalfHeight(100.f);
	body->SetCapsuleRadius(100.f);

	mesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	mesh->SetReceivesDecals(false);
	mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_DragonAnimInstance.ABP_DragonAnimInstance_C'"));

	if (animClass.Succeeded())
		mesh->SetAnimInstanceClass(animClass.Class);

	stateComponent->SetMonsterRowName(TEXT("Dragon"));
	widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//widget->SetRelativeLocation(FVector(0.f, 0.f, body->GetScaledCapsuleHalfHeight() * 2 + 50));
}

void AMonsterDragon::BeginPlay()
{
	Super::BeginPlay();

	AMonsterAIController* controller = GetController<AMonsterAIController>();

	if (controller)
	{
		controller->SetSightRadius(2000.f);
	}

}

void AMonsterDragon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterDragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterDragon::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}


void AMonsterDragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterDragon::NormalAttack()
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
		PointDamageEvent.DamageTypeClass = animInst->bIsStaggerAttack ? UNormalStunDamageType::StaticClass() : UNormalDamageType::StaticClass();

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

void AMonsterDragon::NormalStunAttack()
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

void AMonsterDragon::NormalStaggerAttack()
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

void AMonsterDragon::Attack()
{
	animInst->SetAnimState(EMonsterAnimState::Attack);
	animInst->AttackMontage();
	
}

void AMonsterDragon::Ranged()
{
	animInst->SetAnimState(EMonsterAnimState::Ranged);
	animInst->RangedMontage();
}

void AMonsterDragon::Fire()
{
	FVector CastLocation = mesh->GetSocketLocation(TEXT("Fire"));

	FActorSpawnParameters Param;
	
	AMonsterAIController* controller = GetController<AMonsterAIController>();

	if (controller)
	{
		if (IsValid(controller->GetTarget()))
		{
			FRotator newRotation = GetTargetRotator(CastLocation, controller->GetTarget()->GetActorLocation());

			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			AMonsterProjectile* Projecttile =
				GetWorld()->SpawnActor<AMonsterProjectile>(CastLocation, GetActorForwardVector().Rotation(), Param);

			Projecttile->SetOwnerController(GetController());
			Projecttile->SetOwner(this);
		}
	}
}

void AMonsterDragon::Breath()
{

	FVector CastLocation = mesh->GetSocketLocation(TEXT("Fire"));
	FActorSpawnParameters Param;
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ARangedSkill* RangedSkill =
		GetWorld()->SpawnActor<ARangedSkill>(CastLocation, GetActorRotation(), Param);

	AMonsterAIController* controller = GetController<AMonsterAIController>();

	RangedSkill->SetOwnerActor(this);
	RangedSkill->SetMonsterAIController(controller);
	RangedSkill->SetSpawnCount(5);
	

}
