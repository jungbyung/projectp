// Fill out your copyright notice in the Description page of Project Settings.


#include "ShinobiCharacter.h"
#include "DefaultPlayerState.h"
#include "DefaultPlayerController.h"
#include "Animation/PlayerAnimInstance.h"
#include "skill/Shinobi/DanceWildly.h"
#include "skill/Shinobi/CutWildly.h"
#include "skill/shinobi/RisingSlash.h"
#include "Equipment/EquipmentItem.h"


AShinobiCharacter::AShinobiCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		shinobiMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Undead_Shinobi/Mesh/SK_Undead_Shinobi.SK_Undead_Shinobi'"));

	if (shinobiMesh.Succeeded())
		GetMesh()->SetSkeletalMesh(shinobiMesh.Object);


	equipItem->LoadWeapon(TEXT("Script/Engine.SkeletalMesh'/Game/Undead_Shinobi/Mesh/Separate/Weapon/SK_Undead_Shinobi_Katana.SK_Undead_Shinobi_Katana'"));
	equipItem->Init(GetMesh(), TEXT("Weapon_Right"));
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh>
	//	shinobWeaponMesh(TEXT("Script/Engine.SkeletalMesh'/Game/Undead_Shinobi/Mesh/Separate/Weapon/SK_Undead_Shinobi_Katana.SK_Undead_Shinobi_Katana'"));
	//
	//weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("weapon"));
	//
	//if (shinobiMesh.Succeeded())
	//{
	//	weapon->SetSkeletalMesh(shinobWeaponMesh.Object);
	//	weapon->SetupAttachment(GetMesh(), TEXT("Weapon_Right"));
	//	//weapon->SetReceivesDecals(false);
	//}

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		PlayerAnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Player/Animation/ABP_ShinobiAnimInstance.ABP_ShinobiAnimInstance_C'"));

	if (PlayerAnimClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(PlayerAnimClass.Class);

	TObjectPtr<UDanceWildly> danceWildly = NewObject<UDanceWildly>(this, TEXT("DanceWildly"));
	danceWildly->SetOwnerPawn(this);
	danceWildly->SetSkillIndex(0);
	skillSlots.Add(danceWildly);

	TObjectPtr<UCutWildly> CutWildly = NewObject<UCutWildly>(this, TEXT("CutWildly"));
	CutWildly->SetOwnerPawn(this);
	CutWildly->SetSkillIndex(1);
	skillSlots.Add(CutWildly);

	TObjectPtr<URisingSlash> RisingSlash = NewObject<URisingSlash>(this, TEXT("RisingSlash"));
	RisingSlash->SetOwnerPawn(this);
	RisingSlash->SetSkillIndex(2);
	skillSlots.Add(RisingSlash);

}

void AShinobiCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AShinobiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShinobiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AShinobiCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Dmg = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)&DamageEvent;

	FVector HitLocation = PointDamageEvent->HitInfo.ImpactPoint;
	DrawDebugSphere(GetWorld(), HitLocation, 5.f, 32, FColor::Blue, true, 5.f);
	HitLocation = HitLocation - GetActorLocation();
	HitLocation = HitLocation.GetSafeNormal();

	FVector ActorLocation = GetActorForwardVector();
	ActorLocation = ActorLocation.GetSafeNormal();
	
	float Dot = FVector::DotProduct(ActorLocation, HitLocation);

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("dot hit = %f"), Dot));

	Dmg -= playerState->GetDefense();
	Dmg = Dmg < 1.f ? 1.f : Dmg;

	if (animInst->GetAnimState() == EPlayerAnimState::Block)
	{
		switch (guardState)
		{
		case EGuardState::None:
			break;
		case EGuardState::Parry:
			if (Dot > 0.4f)
			{
				animInst->Counter();
				isBlock = false;
				Dmg = 0;
			}
			else
			{
				animInst->BlockHit2Locomotion(true);
			}
			break;
		case EGuardState::Block:
			if (Dot > 0.4f)
			{
				Dmg = 0;
				animInst->BlockHit();
			}
			else
			{
				animInst->BlockHit2Locomotion(true);
			}
			break;
		default:
			break;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
		FString::Printf(TEXT("monster Dmg = %d, player HP = hp%d/maxHP%d"), (int32)Dmg, playerState->GetHP(),
			playerState->GetHPMax()));

	if (Dmg > 0)
	{
		playerState->AddHP((int32)-Dmg);

		GetController<ADefaultPlayerController>()->SetHPRatio(playerState->GetHP() / (float)playerState->GetHPMax());
		GetController<ADefaultPlayerController>()->SetAttributeHP(playerState->GetHP(), playerState->GetHPMax());
		if (playerState->GetHP() <= 0)
		{
			animInst->Dead();
			
		}
		else
		{
			if (DamageEvent.DamageTypeClass->IsChildOf(UNormalDamageType::StaticClass()))
			{
				animInst->Hit();
			}
			else if (DamageEvent.DamageTypeClass->IsChildOf(UNormalStunDamageType::StaticClass()))
			{
				SetUpdateSkill(nullptr);
				if (Dot < -0.4f)
				{
					animInst->HitDirection(EDirection::Back);
					FVector NewLocation = GetActorLocation() + GetActorForwardVector() * 10.f;
					SetActorLocation(NewLocation);
				}
				else if (Dot < 0.4f)
				{
					FVector Cross = FVector::CrossProduct(ActorLocation, HitLocation);

					if (Cross.Z < 0)
					{
						animInst->HitDirection(EDirection::Left);
						FVector NewLocation = GetActorLocation() + GetActorRightVector() * 10.f;
						SetActorLocation(NewLocation);
					}
					else
					{
						animInst->HitDirection(EDirection::Right);
						FVector NewLocation = GetActorLocation() + GetActorRightVector() * -10.f;
						SetActorLocation(NewLocation);
					}
				}
				else
				{
					animInst->HitDirection(EDirection::Front);

					FVector NewLocation = GetActorLocation() + GetActorForwardVector() * -10.f;
					SetActorLocation(NewLocation);
				}
			}
		}
	}
	return Dmg;
}

void AShinobiCharacter::NormalAttack()
{
	TArray<FHitResult> HitResults;
	FVector start, end;
	FQuat rot;

	start = GetActorLocation() + GetActorForwardVector() * 50.f;
	end = start + GetActorForwardVector() * playerState->GetAttackDistance();

	FCollisionQueryParams param(NAME_None, false, this);

	bool collision = GetWorld()->SweepMultiByChannel(HitResults, start, end,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.f),
		param);


#if ENABLE_DRAW_DEBUG

	FColor color = collision ? FColor::Red : FColor::Green;

	FVector dir = end - start;
	dir.Normalize();

	FQuat quat = FQuat::FindBetweenNormals(FVector::UpVector, dir);

	DrawDebugCapsule(GetWorld(), (start + end) * 0.5f,
		playerState->GetAttackDistance() * 0.5f, 50.f, quat, color, false, 0.5f);


#endif

	if (collision)
	{
		FDamageEvent DmgEvent;

		for (const FHitResult HitResult : HitResults)
		{
			float Dmg = HitResult.GetActor()->TakeDamage(playerState->GetAttackPower(),
				DmgEvent, GetController(), this);
			///Script/Engine.ParticleSystem'/Game/SwordAnimsetPro/Demo/FX/Particles/P_HitPoint.P_HitPoint'

			UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
				TEXT("/Script/Engine.ParticleSystem'/Game/SwordAnimsetPro/Demo/FX/Particles/P_HitPoint.P_HitPoint'"));

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/3/hit-flesh-02-266309.hit-flesh-02-266309'"));

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}

}

void AShinobiCharacter::SetRightWeapon()
{
//	weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_Right"));
	equipItem->SetupWeaponAttachment(GetMesh(), TEXT("Weapon_Right"));
}

void AShinobiCharacter::SetLeftWeapon()
{
//	weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon_Left"));
	equipItem->SetupWeaponAttachment(GetMesh(), TEXT("Weapon_Left"));
}

void AShinobiCharacter::SkillAttack()
{
	if (!updateSkill) return;
	TArray<FHitResult> HitResults;
	FVector start, end;
	FQuat rot;

	start = GetActorLocation() + GetActorForwardVector() * 50.f;
	end = start + GetActorForwardVector() * playerState->GetAttackDistance();

	FCollisionQueryParams param(NAME_None, false, this);

	bool collision = GetWorld()->SweepMultiByChannel(HitResults, start, end,
		FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(50.f),
		param);


#if ENABLE_DRAW_DEBUG

	FColor color = collision ? FColor::Red : FColor::Green;

	FVector dir = end - start;
	dir.Normalize();

	FQuat quat = FQuat::FindBetweenNormals(FVector::UpVector, dir);

	DrawDebugCapsule(GetWorld(), (start + end) * 0.5f,
		playerState->GetAttackDistance() * 0.5f, 50.f, quat, color, false, 0.5f);


#endif

	if (collision)
	{
		FDamageEvent DmgEvent;

		for (const FHitResult HitResult : HitResults)
		{
			float dmg = updateSkill->GetSkillOption().attackPower / (float)updateSkill->GetSkillOption().attackCount +
				playerState->GetAttackPower();
			HitResult.GetActor()->TakeDamage(dmg, DmgEvent, GetController(), this);
			///Script/Engine.ParticleSystem'/Game/SwordAnimsetPro/Demo/FX/Particles/P_HitPoint.P_HitPoint'

			UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
				TEXT("/Script/Engine.ParticleSystem'/Game/SwordAnimsetPro/Demo/FX/Particles/P_HitPoint.P_HitPoint'"));

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());

			USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/3/hit-flesh-02-266309.hit-flesh-02-266309'"));

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		}
	}

}

void AShinobiCharacter::Hit()
{
}

void AShinobiCharacter::HitDir(const FVector& HitLocation)
{
}
