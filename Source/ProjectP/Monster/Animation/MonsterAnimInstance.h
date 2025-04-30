// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();
protected:
	static UDataTable* animData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName animName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterAnimState monsterAnimState = EMonsterAnimState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<UAnimSequence>> animMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> attackSectionNameArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> rangedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> rangedSectionNameArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float hitAlpha = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 attackRnd = -1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 skillRand = -1;

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
	int32 attackSectionIndex = 0;
	int32 rangedSectionIndex = 0;

	float stunTime = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDirection hitDirection = EDirection::None;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EDirection dodgeDirection = EDirection::None;


public:
	virtual void PostInitProperties();
	virtual void NativeBeginPlay();

public:
	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_Attack();
	UFUNCTION()
	void AnimNotify_HitEnd();
	UFUNCTION()
	void AnimNotify_Dead();
	UFUNCTION()
	void AnimNotify_Cast();
	UFUNCTION()
	void AnimNotify_CastEnd();
	UFUNCTION()
	void AnimNotify_NormalStaggerAttack();

	UFUNCTION()
	void MontageEnd(UAnimMontage* Montage, bool Interrupted);
	UFUNCTION()
	void AnimNotify_Fire();
	UFUNCTION()
	void AnimNotify_Breath();
	UFUNCTION()
	void AnimNotify_DodgeEnd();
	UFUNCTION()
	void AnimNotify_DodgeMoveEnd();

public:

	bool bIsStaggerAttack = false;
	bool bIsFollowUpAttack = false;
	int32 followUpAttackIndex = -1;

	void SetAnimState(EMonsterAnimState MonsterAnimState);
	void Hit() { hitAlpha = 1.f; }
	void AttackRand();
	void SkillRand();
	void AttackMontage();
	void AttackMontage(int32 Index);
	void RangedMontage();

	bool AttackPattern();

	void SetHitDirection(EDirection HitDirection);
	void SetDodgeDirection(EDirection DodgeDirection) { dodgeDirection = DodgeDirection; }
	EDirection GetHitDirection() { return hitDirection; }
	EDirection GetDodgeDirection() { return dodgeDirection; }

	bool MontageIsPlaying() { return Montage_IsPlaying(attackMontage); }

	EMonsterAnimState GetAnimState() { return monsterAnimState; }

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
};
