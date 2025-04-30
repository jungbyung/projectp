// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();
protected:
	static UDataTable* animData;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName animName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> animMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> locomotionMap;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> attackSectionNameArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWalkDirection dir = EWalkDirection::Forward;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDirection hitDir = EDirection::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isRun = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 attackSectionIndex = 0;

	bool isAttackCombo = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isAttack = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimState playerAnimState = EPlayerAnimState::Locomotion;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EBlock blockAnimState = EBlock::In;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FFootIKResult footIKL;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FFootIKResult footIKR;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator footRotLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator footRotRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float hipOffset;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float footOffsetLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float footOffsetRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float hitAlpha = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int skillIndex = -1;

	bool toLocomotion = false;

public:
	EPlayerAnimState GetAnimState() { return playerAnimState; }
	void SetAnimState(EPlayerAnimState AnimState){ playerAnimState = AnimState; }
public:
	virtual void PostInitProperties();
	virtual void NativeInitializeAnimation();
	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaSeconds);


	UFUNCTION()
	void AnimNotify_Attack();
	UFUNCTION()
	void AnimNotify_RightWeapon();
	UFUNCTION()
	void AnimNotify_LeftWeapon();
	UFUNCTION()
	void AnimNotify_AttackCombo();
	UFUNCTION()
	void AnimNotify_HitEnd();
	UFUNCTION()
	void AnimNotify_SkillEnd();
	UFUNCTION()
	void AnimNotify_DodgeEnd(); 
	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool Interrupted);
	UFUNCTION()
	void AnimNotify_SkillAttack();

	UFUNCTION()
	void AnimNotify_Block();

	UFUNCTION()
	void AnimNotify_BlockOut();

	UFUNCTION()
	void AnimNotify_BlockCounter();

	UFUNCTION()
	void AnimNotify_BlockCounterEnd();

	UFUNCTION()
	void AnimNotify_HitStunEnd();
	UFUNCTION()
	void AnimNotify_BlockHitEnd();

	UFUNCTION()
	void AnimNotify_NormalStaggerAttack();
public:
	void SetAnimData(const FName& Name);
	void SetDir(EWalkDirection Direction);
	void SetSpeed(float Speed);
	void SetRun(bool Run);
	bool GetRun() { return isRun; }
	void Counter();
	void BlockIn();
	void BlockOut();
	void BlockHit();
	void BlockHit2Locomotion(bool Locomotion);

	void SetSkillIndex(int Index) { skillIndex = Index; }
	bool GetIsAttack() { return Montage_IsPlaying(attackMontage); }
	bool GetFindAnim(const FName& AnimName) { return animMap.Find(AnimName) != nullptr ? true : false; }
	void Hit() { hitAlpha = 1.f; }
	void Dead();
	void HitDirection(EDirection HitDirection);

	EWalkDirection GetDir() { return dir; }

	void SetFootIkInfo(const FFootIKResult& FootIKL,
		const FFootIKResult& FootIKR)
	{
		footIKL = FootIKL;
		footIKR = FootIKR;
	}

	void SetFootRotation(const FRotator& Left, const FRotator& Right)
	{
		footRotLeft = Left;
		footRotRight = Right;
	}

	void SetHipOffset(float Offset)
	{
		hipOffset = Offset;
	}
	void SetFootOffset(float Left, float Right)
	{
		footOffsetLeft = Left;
		footOffsetRight = Right;
	}

	void Attack();
};
