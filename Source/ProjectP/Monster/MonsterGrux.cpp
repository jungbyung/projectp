// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterGrux.h"
#include "Animation/MonsterAnimInstance.h"
#include "AI/MonsterAIController.h"
#include "../player/PlayerCharacter.h"

AMonsterGrux::AMonsterGrux()
{
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));

	if (skeletalMesh.Succeeded())
		mesh->SetSkeletalMeshAsset(skeletalMesh.Object);

	body->SetCapsuleHalfHeight(100.f);
	body->SetCapsuleRadius(60.f);

	mesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		animClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Monster/ABP_GruxAnimInstance.ABP_GruxAnimInstance_C'"));

	if (animClass.Succeeded())
		mesh->SetAnimInstanceClass(animClass.Class);

	stateComponent->SetMonsterRowName(TEXT("Grux"));

	widget->SetupAttachment(mesh);

	static ConstructorHelpers::FClassFinder<UHeadWidget>
		HeadWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/HUD/WB_HeadWidget.WB_HeadWidget_C'"));

	if (HeadWidget.Succeeded())
	{
		headWidgetClass = HeadWidget.Class;
		widget->SetWidgetClass(HeadWidget.Class);

		widget->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
		widget->SetWidgetSpace(EWidgetSpace::World);

		widget->SetDrawSize(FVector2D(150.f, 50.f));
		widget->SetPivot(FVector2d(0.5f, 0.5f));
		widget->SetTranslucentSortPriority(0);
		widget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	widget->SetRelativeLocation(FVector(0.f, 0.f, body->GetScaledCapsuleHalfHeight() * 2 + 50));
}

void AMonsterGrux::BeginPlay()
{
	Super::BeginPlay();

	//stateComponent->setname
}

void AMonsterGrux::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonsterGrux::Tick(float DeltaTime)
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

void AMonsterGrux::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterGrux::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMonsterGrux::NormalAttack()
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
		stateComponent->GetAttackDistance() * 0.5f, 50.f, quat, color, false, 0.5f);


#endif

	if (collision)
	{	
		FPointDamageEvent PointDamageEvent;
		PointDamageEvent.HitInfo = HitResult;
		PointDamageEvent.Damage = stateComponent->GetAttackPower();
		PointDamageEvent.DamageTypeClass = UNormalDamageType::StaticClass();


		float Dmg = HitResult.GetActor()->TakeDamage(stateComponent->GetAttackPower(),
			PointDamageEvent, GetController(), this);

		UE_LOG(ProjectP, Warning, TEXT("%s"), *HitResult.ToString());

		APlayerCharacter* Player = Cast<APlayerCharacter>(HitResult.GetActor());

		if (Player)
		{

			UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
				TEXT("/Script/Engine.ParticleSystem'/Game/ParagonRampage/FX/Particles/Abilities/Primary/FX/P_Rampage_Enraged_Impact.P_Rampage_Enraged_Impact'"));

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			if (Player->GuardState() == EGuardState::Block)
			{
				USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
					TEXT("/Script/Engine.SoundWave'/Game/Sound/3/metal-hit-25-193291.metal-hit-25-193291'"));

				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			}
			else if (Player->GuardState() == EGuardState::Parry)
			{

				USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
					TEXT("/Script/Engine.SoundWave'/Game/Sound/1/Whoosh_1-1.Whoosh_1-1'"));

				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			}
			else
			{
				USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
					TEXT("/Script/Engine.SoundWave'/Game/Sound/3/fist-punch-or-kick-7171.fist-punch-or-kick-7171'"));

				UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			}
		}
	}
}
