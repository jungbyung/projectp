// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "inputactionvalue.h"
#include "GameFramework/Character.h"
#include "../common/characterinterface.h"
#include "Inventory/InventoryInterface.h"
#include "Inventory/InventoryComponent.h"
#include "skill/skillinterface.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECTP_API APlayerCharacter : public ACharacter, 
	public IGenericTeamAgentInterface, public ICharacterInterface, public IInventoryInterface,
	public ISkillInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> springArm;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> camera;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> renderTargetCamera;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneCaptureComponent2D> renderTargetImage;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> weapon;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UEquipmentItem> equipItem;

	EGuardState guardState= EGuardState::None;
	TObjectPtr<class ADefaultPlayerState> playerState;

	TObjectPtr<class UPlayerAnimInstance> animInst;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UFootIKComponent> footIK;

	UPROPERTY(VisibleAnywhere)
	FGenericTeamId myTeam = FGenericTeamId::NoTeam;
	uint8 teamID = 1;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class USkillBase>> skillSlots;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USkillBase> updateSkill;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInventoryComponent>	inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float dodgeDistance = 25.f;
	float dodgeTime = 0.f;
	float dodgeTimeMax = 0.4f;

	bool isBlock = false;
	bool isParry = false;
	float blockAccTime = 0.f;
	float blockTime = 0.5f;


	float staminaRecoveryTimeMax = 1.f;
	float staminaRecoveryTime = 0.f;
	int32 dodgeStaminaCurrent = 0;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	void SetTeamID(uint8 TeamID);
	void SetUpdateSkill(class USkillBase* SkillBase);
	void SetAnimState(EPlayerAnimState AnimState);
	void SetSkillIndex(int Index);
	class UPlayerAnimInstance* GetAnimInst();
	class ADefaultPlayerState* GetDefaultPlayerState();
	void UseStamina(int32 Stamina);
	void AddStamina(int32 Stamina);
	void SetSkillCoolTime(int32 Index, float CoolTime);
	void SetSkillUseStamina(int32 Index, int32 Stamina);
	void SkillUse(int32 Index);
	void SetSkillOption(FSkillOption SkillOption, int32 Index);
	void AddHP(int32 HP);
	void SetSkillInfo(int32 Index);
	void AttackPowerUp(int32 AttackPower);
	void DefenseUp(int32 Defense);

	void AddBuff(class UInventoryItem* InvenItem);
	
	void BlockIn();
	void BlockOut();


	EGuardState GuardState();
private:
	void Move(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void SkillActive1(const FInputActionValue& Value);
	void SkillActive2(const FInputActionValue& Value);
	void SkillActive3(const FInputActionValue& Value);
	void SkillActive4(const FInputActionValue& Value);
	void CameraRotation(const FInputActionValue& Value);
	void InventoryWidget(const FInputActionValue& Value);
	void SkillWidget(const FInputActionValue& Value);
	void StatusWidget(const FInputActionValue& Value);
	void ItemAction(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void UseQuickItem(const FInputActionValue& Value);
	void Block(const FInputActionValue& Value);

public:
	virtual void NormalAttack();
	virtual FGenericTeamId GetGenericTeamId() const;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
	virtual class UInventoryComponent* GetInventoryComponent();
	virtual TArray<class USkillBase*> GetSkillSlots();
	virtual void SetRightWeapon();
	virtual void SetLeftWeapon();
	virtual void SkillAttack();

	virtual void Hit();
	virtual void HitDir(const FVector& HitLocation);

public:
	virtual void SetFootIkInfo(const FFootIKResult& FootIKL, const FFootIKResult& FootIKR);
	virtual void SetRootCapsuleHalfHeight(float Height);
	virtual float GetRootCapsuleHalfHeight();
	virtual void SetFootRotation(const FRotator& Left, const FRotator& Right);
	virtual void SetHipOffset(float Offset);
	virtual void SetFootOffset(float Left, float Right);
};
