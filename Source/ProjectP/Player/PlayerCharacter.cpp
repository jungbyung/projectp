// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/InputData.h"
#include "DefaultPlayerController.h"
#include "Animation/PlayerAnimInstance.h"
#include "DefaultPlayerState.h"
#include "../Item/InventoryItem.h"
#include "../item/ItemBase.h"
#include "../common/FootIKComponent.h"
#include "skill/skillbase.h"
#include "equipment/equipmentitem.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	footIK = CreateDefaultSubobject<UFootIKComponent>(TEXT("footIK"));
	equipItem = CreateDefaultSubobject<UEquipmentItem>(TEXT("Equipment"));
	
	equipItem->SetupAttachment(GetMesh());
	footIK->SetOwner(this, GetMesh());
	footIK->SetOwnerOffset(GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight());

	springArm->SetupAttachment(GetMesh());
	camera->SetupAttachment(springArm);
	GetMesh()->SetReceivesDecals(false);

	springArm->TargetArmLength = 500.f;

	springArm->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	springArm->SetRelativeRotation(FRotator(-10.f, 90.f, 0.f));

	//GetCharacterMovement

	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//bUseControllerRotationYaw = false;
	//bUseControllerRotationPitch = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetMesh()->SetReceivesDecals(false);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	playerState = GetPlayerState<ADefaultPlayerState>();
	animInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());


	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (IsValid(playerController))
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

		const UInputData* inputData = GetDefault<UInputData>();

		subSystem->AddMappingContext(inputData->context, 0);

		//playerController->initattri

	}

	ADefaultPlayerController* dpc = Cast<ADefaultPlayerController>(GetController());

	if (IsValid(dpc))
	{
		dpc->InitAttribute();
	}


	inventory->AddItem(TEXT("LifePotion"));
	inventory->AddItem(TEXT("StaminaPotion"));
	inventory->AddItem(TEXT("PowerPotion"));
	inventory->AddItem(TEXT("DefensePotion"));

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector forward = GetMovementComponent()->Velocity;
	forward.Z = 0;
	forward = forward.GetSafeNormal();
	DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + forward * 100.f,
		5.f, FColor::Red);

	if (animInst->GetAnimState() == EPlayerAnimState::Dodge)
	{
		dodgeTime += DeltaTime;
		float Dist = dodgeTime / dodgeTimeMax;

		FVector dir = GetActorForwardVector();
		
		switch (animInst->GetDir())
		{
		case EWalkDirection::Forward:
			dir = GetActorForwardVector();
			break;
		case EWalkDirection::ForwardRight:
			dir = GetActorForwardVector() + GetActorRightVector();
			break;
		case EWalkDirection::ForwardLeft:
			dir = GetActorForwardVector() - GetActorRightVector();
			break;
		case EWalkDirection::Back:
			dir = -GetActorForwardVector();
			break;
		case EWalkDirection::BackRight:
			dir = -GetActorForwardVector() + GetActorRightVector();
			break;
		case EWalkDirection::BackLeft:
			dir = -GetActorForwardVector() - GetActorRightVector();
			break;
		case EWalkDirection::Left:
			dir = -GetActorRightVector();
			break;
		case EWalkDirection::Right:
			dir = GetActorRightVector();
			break;
		default:
			break;
		}

		dir = dir.GetSafeNormal();

		FVector newLocation = FMath::Lerp<FVector>(GetActorLocation(),
			GetActorLocation() + dir * dodgeDistance, Dist);
		
		float stamina = FMath::Lerp<float>(50.f*Dist, 50.f, Dist);
		dodgeStaminaCurrent = stamina - dodgeStaminaCurrent;
		
		UE_LOG(ProjectP, Warning, TEXT("%d"), dodgeStaminaCurrent);
		UseStamina(dodgeStaminaCurrent);
		dodgeStaminaCurrent = stamina;
		SetActorLocation(newLocation);
		//AddMovementInput(GetActorForwardVector(), Dist);

		if (dodgeTime >= dodgeTimeMax)
		{
			dodgeTime = 0.f;
			dodgeStaminaCurrent = 0;
			animInst->SetAnimState(EPlayerAnimState::Locomotion);
		}

	}
	if (animInst->GetRun() && !GetCharacterMovement()->Velocity.IsZero())
	{
		UseStamina(1);

	}
	staminaRecoveryTime += DeltaTime;
	if (staminaRecoveryTime > staminaRecoveryTimeMax)
	{
		AddStamina(1);
	}

	for (int32 i = 0; i < skillSlots.Num(); ++i)
	{
		skillSlots[i]->UpdateCoolTime(DeltaTime);
		if (updateSkill)
		{
			if (updateSkill->GetActive())
				staminaRecoveryTime = 0.f;
		}
	}
	if (isBlock)
	{
		if (isParry)
		{
			blockAccTime += DeltaTime;

			if (blockAccTime > blockTime)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("parry end"));
				isParry = false;
				blockAccTime = 0.f;
				guardState = EGuardState::Block;
				equipItem->UpdateGuard(guardState);
			}
		}
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(enhancedInput))
	{
		const UInputData* InputData = GetDefault<UInputData>();
		/*
		void InventoryWidget(const FInputActionValue & Value);
		void SkillWidget(const FInputActionValue & Value);
		void StatusWidget(const FInputActionValue & Value);
		*/
		enhancedInput->BindAction(InputData->move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		enhancedInput->BindAction(InputData->rotation, ETriggerEvent::Triggered, this, &APlayerCharacter::CameraRotation);
		enhancedInput->BindAction(InputData->attack, ETriggerEvent::Started, this, &APlayerCharacter::Attack);
		enhancedInput->BindAction(InputData->skillActive1, ETriggerEvent::Started, this, &APlayerCharacter::SkillActive1);
		enhancedInput->BindAction(InputData->skillActive2, ETriggerEvent::Started, this, &APlayerCharacter::SkillActive2);
		enhancedInput->BindAction(InputData->skillActive3, ETriggerEvent::Started, this, &APlayerCharacter::SkillActive3);
		enhancedInput->BindAction(InputData->skillActive4, ETriggerEvent::Started, this, &APlayerCharacter::SkillActive4);
		enhancedInput->BindAction(InputData->itemAction, ETriggerEvent::Started, this, &APlayerCharacter::ItemAction);
		enhancedInput->BindAction(InputData->run, ETriggerEvent::Triggered, this, &APlayerCharacter::Run);
		enhancedInput->BindAction(InputData->run, ETriggerEvent::Completed, this, &APlayerCharacter::Run);
		enhancedInput->BindAction(InputData->dodge, ETriggerEvent::Started, this, &APlayerCharacter::Dodge);
		enhancedInput->BindAction(InputData->inventoryWidget, ETriggerEvent::Started, this, &APlayerCharacter::InventoryWidget);
		enhancedInput->BindAction(InputData->useQuickItem, ETriggerEvent::Started, this, &APlayerCharacter::UseQuickItem);
		enhancedInput->BindAction(InputData->statusWidget, ETriggerEvent::Started, this, &APlayerCharacter::StatusWidget);
		enhancedInput->BindAction(InputData->block, ETriggerEvent::Started, this, &APlayerCharacter::Block);
		enhancedInput->BindAction(InputData->block, ETriggerEvent::Completed, this, &APlayerCharacter::Block);
	}
}

float APlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	//if (animInst->GetPlayerAnimState() == EPlayerAnimState::Dead) return;
	if (!IsValid(animInst)) return;

	if (animInst->GetAnimState() != EPlayerAnimState::Locomotion) return;

	FVector Axis = Value.Get<FVector>();



	if (Axis.X > 0.f && FMath::IsNearlyZero(Axis.Y))
	{
		animInst->SetDir(EWalkDirection::Forward);

	}
	else if (Axis.X < 0.f && FMath::IsNearlyZero(Axis.Y))
	{
		animInst->SetDir(EWalkDirection::Back);
	}
	else if (Axis.Y > 0.f && FMath::IsNearlyZero(Axis.X))
	{
		animInst->SetDir(EWalkDirection::Right);
	}
	else if (Axis.Y < 0.f && FMath::IsNearlyZero(Axis.X))
	{
		animInst->SetDir(EWalkDirection::Left);
	}
	else if (Axis.X > 0.f && Axis.Y > 0.f)
		animInst->SetDir(EWalkDirection::ForwardRight);
	else if (Axis.X > 0.f && Axis.Y < 0.f)
		animInst->SetDir(EWalkDirection::ForwardLeft);
	else if (Axis.X < 0.f && Axis.Y > 0.f)
		animInst->SetDir(EWalkDirection::BackRight);
	else if (Axis.X < 0.f && Axis.Y < 0.f)
		animInst->SetDir(EWalkDirection::BackLeft);

	FRotator SpringArmRot = springArm->GetComponentRotation();
	SpringArmRot.Pitch = 0.f;
	SpringArmRot.Roll = 0.f;
	GetController()->SetControlRotation(SpringArmRot);
	SpringArmRot = springArm->GetRelativeRotation();
	SpringArmRot.Yaw = 90.f;
	springArm->SetRelativeRotation(SpringArmRot);

	AddMovementInput(GetActorForwardVector(), Axis.X);
	AddMovementInput(GetActorRightVector(), Axis.Y);
}

void APlayerCharacter::Attack(const FInputActionValue& Value)
{
	//if (IsValid(updateSkill))
	//{
	//	updateSkill->UpdateEnd();
	//	SetUpdateSkill(nullptr);
	//}

	if (!IsValid(updateSkill) && animInst->GetAnimState() != EPlayerAnimState::NormalStagger)
	{
		animInst->Attack();

	}
}

void APlayerCharacter::SkillActive1(const FInputActionValue& Value)
{
	SkillUse(0);
}
void APlayerCharacter::SkillActive2(const FInputActionValue& Value)
{
	SkillUse(1);
}

void APlayerCharacter::SkillActive3(const FInputActionValue& Value)
{
	SkillUse(2);
}

void APlayerCharacter::SkillActive4(const FInputActionValue& Value)
{
	SkillUse(3);
}



void APlayerCharacter::CameraRotation(const FInputActionValue& Value)
{
	FVector Axis = Value.Get<FVector>();

	float rotPitch = Axis.Y * 180.f * GetWorld()->GetDeltaSeconds();
	float rotYaw = Axis.X * 180.f * GetWorld()->GetDeltaSeconds();

	springArm->AddRelativeRotation(FRotator(rotPitch, rotYaw, 0.f));

	FRotator rot = springArm->GetRelativeRotation();

	if (rot.Pitch < -70.f)
		rot.Pitch = -70.f;
	else if (rot.Pitch > 70.f)
		rot.Pitch = 70.f;

	//if (rotYaw < -90.f)
	//	rotYaw += 360.f;
	//else if (rotYaw > 270.f)
	//	rotYaw -= 360.f;

	if (rot.Yaw < -90.f)
		rot.Yaw += 360.f;
	else if (rot.Yaw > 270.f)
		rot.Yaw -= 360.f;

	springArm->SetRelativeRotation(rot);
	//AddControllerYawInput(rotYaw);
}

void APlayerCharacter::InventoryWidget(const FInputActionValue& Value)
{
	GetController<ADefaultPlayerController>()->ToggleInventory();

	//USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
	//	TEXT("/Script/Engine.SoundWave'/Game/Free_Sounds_Pack/wav/Interface_1-1.Interface_1-1'"));
	//
	//UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, GetActorLocation(), GetActorRotation());

}

void APlayerCharacter::SkillWidget(const FInputActionValue& Value)
{
}

void APlayerCharacter::StatusWidget(const FInputActionValue& Value)
{
	GetController<ADefaultPlayerController>()->ToggleAttribute();

}

void APlayerCharacter::ItemAction(const FInputActionValue& Value)
{
}

void APlayerCharacter::Run(const FInputActionValue& Value)
{
	bool run = Value.Get<bool>();

	if (playerState->GetStamina() > 0 && !GetMovementComponent()->Velocity.IsNearlyZero())
	{
		animInst->SetRun(run);
		playerState->SetWalkAndRun(run);
	}
	else
	{
		animInst->SetRun(false);
		playerState->SetWalkAndRun(false);
	}
	GetController<ADefaultPlayerController>()->SetAttributeMoveSpeed(GetCharacterMovement()->MaxWalkSpeed);

}

void APlayerCharacter::Dodge(const FInputActionValue& Value)
{
	if (animInst->GetAnimState() == EPlayerAnimState::Locomotion &&
		!animInst->GetIsAttack() && playerState->GetStamina() > 30)
	{
		animInst->SetAnimState(EPlayerAnimState::Dodge);
	}
}

void APlayerCharacter::UseQuickItem(const FInputActionValue& Value)
{
	inventory->UseQuickItem();
}

void APlayerCharacter::Block(const FInputActionValue& Value)
{
	bool block = Value.Get<bool>();

	if (block)
	{
		guardState = EGuardState::None;
		animInst->BlockIn();
	}
	else
	{
		animInst->BlockOut();
		guardState = EGuardState::None;
	}

}

void APlayerCharacter::NormalAttack()
{
}

void APlayerCharacter::SetTeamID(uint8 TeamID)
{
	teamID = TeamID;
}

void APlayerCharacter::SetUpdateSkill(USkillBase* SkillBase)
{
	updateSkill = SkillBase;
}

void APlayerCharacter::SetAnimState(EPlayerAnimState AnimState)
{
	animInst->SetAnimState(AnimState);
}

void APlayerCharacter::SetSkillIndex(int Index)
{
	animInst->SetSkillIndex(Index);
}

UPlayerAnimInstance* APlayerCharacter::GetAnimInst()
{
	return animInst;
}

ADefaultPlayerState* APlayerCharacter::GetDefaultPlayerState()
{
	return playerState;
}


void APlayerCharacter::UseStamina(int32 Stamina)
{
	staminaRecoveryTime = 0.f;
	playerState->UseStamina(Stamina);
	GetController<ADefaultPlayerController>()->SetStaminaRatio(playerState->GetStamina() / (float)playerState->GetStaminaMax());
	GetController<ADefaultPlayerController>()->SetAttributeStemina(playerState->GetStamina(), playerState->GetStaminaMax());

}

void APlayerCharacter::AddStamina(int32 Stamina)
{
	playerState->AddStamina(Stamina);
	GetController<ADefaultPlayerController>()->SetStaminaRatio(playerState->GetStamina() / (float)playerState->GetStaminaMax());
	GetController<ADefaultPlayerController>()->SetAttributeStemina(playerState->GetStamina(), playerState->GetStaminaMax());

}

void APlayerCharacter::SetSkillCoolTime(int32 Index, float CoolTime)
{
	if (skillSlots[Index])
		skillSlots[Index]->SetSkillCoolTime(CoolTime);
}

void APlayerCharacter::SetSkillUseStamina(int32 Index, int32 Stamina)
{
	if (skillSlots[Index])
		skillSlots[Index]->SetUseStamina(Stamina);
}

void APlayerCharacter::SkillUse(int32 Index)
{
	if (Index >= skillSlots.Num()) return;
	if (!IsValid(updateSkill))
	{

		if (IsValid(skillSlots[Index]))
		{
			FString str = TEXT("Skill") + FString::FromInt(Index+1);


			if (!skillSlots[Index]->GetActive() &&
				playerState->GetStamina() >= skillSlots[Index]->GetUseStamina() &&
				animInst->GetFindAnim(FName(str)) && 
				animInst->GetAnimState() != EPlayerAnimState::NormalStagger)
			{
				skillSlots[Index]->Use();
				animInst->SetSkillIndex(Index);
				UseStamina(skillSlots[Index]->GetUseStamina());
			}
		}
	}
}

void APlayerCharacter::SetSkillOption(FSkillOption SkillOption, int32 Index)
{
	if (IsValid(skillSlots[Index]))
	{
		skillSlots[Index]->SetSkillOption(SkillOption);
	}
}

void APlayerCharacter::AddHP(int32 HP)
{
	playerState->AddHP(HP);
	GetController<ADefaultPlayerController>()->SetHPRatio(playerState->GetHP() / (float)playerState->GetHPMax());
	GetController<ADefaultPlayerController>()->SetAttributeHP(playerState->GetHP(), playerState->GetHPMax());
}

void APlayerCharacter::SetSkillInfo(int32 Index)
{
	if (Index < 0)
	{
		GetController<ADefaultPlayerController>()->SetSkillInfo(nullptr, false);
	}
	else if (skillSlots[Index])
	{
		GetController<ADefaultPlayerController>()->SetSkillInfo(skillSlots[Index], true);
	}
}

void APlayerCharacter::AttackPowerUp(int32 AttackPower)
{
	playerState->SetAttackPowerUp(AttackPower);
	GetController<ADefaultPlayerController>()->SetAttributeAttackPower(playerState->GetAttackPower());

}

void APlayerCharacter::DefenseUp(int32 Defense)
{
	playerState->SetDefenseUp(Defense);
	GetController<ADefaultPlayerController>()->SetAttributeDefense(playerState->GetDefense());
}

void APlayerCharacter::AddBuff(UInventoryItem* InvenItem)
{
	GetController<ADefaultPlayerController>()->AddBuffItem(InvenItem->GetItem());
}

void APlayerCharacter::BlockIn()
{
	if (animInst->GetAnimState() != EPlayerAnimState::NormalStagger)
	{
		isBlock = true;
		isParry = true;
		guardState = EGuardState::Parry;
		equipItem->UpdateGuard(guardState);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("parry start"));
	}
}

void APlayerCharacter::BlockOut()
{
	isBlock = false;
	blockAccTime = 0.f;
	guardState = EGuardState::None;
	equipItem->UpdateGuard(guardState);
}


EGuardState APlayerCharacter::GuardState()
{
	if(animInst->GetAnimState() == EPlayerAnimState::Block)
		return guardState;
	return EGuardState::None;
}

FGenericTeamId APlayerCharacter::GetGenericTeamId() const
{
	return FGenericTeamId(teamID);
}

ETeamAttitude::Type APlayerCharacter::GetTeamAttitudeTowards(const AActor& Other) const
{
	const IGenericTeamAgentInterface* otherTeam = Cast<const IGenericTeamAgentInterface>(&Other);

	if (!otherTeam) return ETeamAttitude::Neutral;
	else
	{
		if (otherTeam->GetGenericTeamId().GetId() == 255)
			return ETeamAttitude::Neutral;
	}
	return teamID == otherTeam->GetGenericTeamId().GetId() ?
		ETeamAttitude::Friendly : ETeamAttitude::Hostile;
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent()
{
	return inventory;
}

TArray<class USkillBase*> APlayerCharacter::GetSkillSlots()
{
	return skillSlots;
}

void APlayerCharacter::SetRightWeapon()
{
}

void APlayerCharacter::SetLeftWeapon()
{
}

void APlayerCharacter::SkillAttack()
{
}

void APlayerCharacter::Hit()
{
}

void APlayerCharacter::HitDir(const FVector& HitLocation)
{
}

void APlayerCharacter::SetFootIkInfo(const FFootIKResult& FootIKL, const FFootIKResult& FootIKR)
{
	animInst->SetFootIkInfo(FootIKL, FootIKR);
}

void APlayerCharacter::SetRootCapsuleHalfHeight(float Height)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(Height);
}

float APlayerCharacter::GetRootCapsuleHalfHeight()
{
	return GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
}

void APlayerCharacter::SetFootRotation(const FRotator& Left, const FRotator& Right)
{
	animInst->SetFootRotation(Left, Right);
}

void APlayerCharacter::SetHipOffset(float Offset)
{
	animInst->SetHipOffset(Offset);
}

void APlayerCharacter::SetFootOffset(float Left, float Right)
{
	animInst->SetFootOffset(Left, Right);
}
