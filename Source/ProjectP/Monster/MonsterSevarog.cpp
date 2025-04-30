// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSevarog.h"
#include "Projectile/MonsterProjectile.h"

AMonsterSevarog::AMonsterSevarog()
{
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));

	if (skeletalMesh.Succeeded())
		mesh->SetSkeletalMeshAsset(skeletalMesh.Object);

	body->SetCapsuleHalfHeight(150.f);
	body->SetCapsuleRadius(60.f);

	mesh->SetRelativeLocation(FVector(0.f, 0.f, -150.f));
	mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_SevarogAniminstance.ABP_SevarogAniminstance_C'"));

	if (animClass.Succeeded())
		mesh->SetAnimInstanceClass(animClass.Class);

	stateComponent->SetMonsterRowName(TEXT("Sevarog"));

	widget->SetRelativeLocation(FVector(0.f, 0.f, body->GetScaledCapsuleHalfHeight()* 2 + 50));

	isSkill = true;
}

void AMonsterSevarog::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterSevarog::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterSevarog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCameraManager* CameraMgr = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	if (CameraMgr && widget)
	{
		FRotator Rot = GetTargetRotator(widget->GetComponentLocation(),
			CameraMgr->GetCameraLocation());

		widget->SetWorldRotation(FRotator(0.f, Rot.Yaw, 0.f));

		FVector CameraPos = CameraMgr->GetCameraLocation();
		FVector WidgetPos = widget->GetComponentLocation();

		float Distance = FVector::Distance(CameraPos, WidgetPos);

		if (Distance >= 5000.f)
		{
			widget->SetHiddenInGame(true);
		}
		else
		{
			widget->SetHiddenInGame(false);
		}
		float ScaleFactor = FMath::Clamp(Distance / 1000.f, 0.5f, 1.5f);

		widget->SetWorldScale3D(FVector(1.f, ScaleFactor, ScaleFactor));
	}


}

void AMonsterSevarog::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterSevarog::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterSevarog::NormalAttack()
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

			///Script/Engine.ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_Rampage_Enraged_Impact.P_Rampage_Enraged_Impact'

			UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
				TEXT("/Script/Engine.ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_Rampage_Enraged_Impact.P_Rampage_Enraged_Impact'"));

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/3/fist-punch-or-kick-7171.fist-punch-or-kick-7171'"));

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

		}
	}
}

void AMonsterSevarog::UseSkill()
{
	Super::UseSkill();
	FVector CastLocation = mesh->GetSocketLocation(TEXT("hand_lSocket"));
	FRotator CastRotation = mesh->GetSocketRotation(TEXT("hand_lSocket"));

	FActorSpawnParameters Param;

	FRotator newRotation = GetTargetRotator(CastLocation, projectileDir); 

	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMonsterProjectile* Projecttile =
		GetWorld()->SpawnActor<AMonsterProjectile>(CastLocation, newRotation, Param);

	Projecttile->SetOwnerController(GetController());
	Projecttile->SetOwner(this);
}
