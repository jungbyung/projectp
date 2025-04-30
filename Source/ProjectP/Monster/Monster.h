// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgamecommon.h"
#include "GameFramework/Pawn.h"
#include "MonsterStateComponent.h"
#include "MonsterMovementComponent.h"
#include <Components/WidgetComponent.h>
#include "../Common/CharacterInterface.h"
#include "Monster.generated.h"

UCLASS()
class PROJECTP_API AMonster : public APawn, public ICharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCapsuleComponent> body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMonsterMovementComponent> movement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMonsterStateComponent> stateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UMonsterAnimInstance> animInst;

	TObjectPtr<class AMonsterSpawner> spawner = nullptr;
	TArray<TObjectPtr<UMaterialInstanceDynamic>> materialArray;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> patrolPosArray;
	int32 patrolPosIndex = 1;

	FVector projectileDir = FVector::ZeroVector;

	bool isSkill = false;

	bool dissolveEnable = false;
	float dissolve = 1.4f;
	float dissolveTime = 0.f;
	float dissolveTimeMax = 3.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> widget;

	TObjectPtr<class UHeadWidget> headWidget;
	TSubclassOf<class UHeadWidget> headWidgetClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UFootIKComponent> footIK;


public:
	virtual void SetFootIkInfo(const FFootIKResult& FootIKL,const FFootIKResult& FootIKR) ;
	virtual void SetRootCapsuleHalfHeight(float Height);
	virtual float GetRootCapsuleHalfHeight() ;
	virtual void SetFootRotation(const FRotator& Left, const FRotator& Right);
	virtual void SetHipOffset(float Offset) ;
	virtual void SetFootOffset(float Left, float Right) ;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UMonsterStateComponent* GetMonsterState() { return stateComponent; }
	UCapsuleComponent* GetCapsule() { return body; }
	class UMonsterAnimInstance* GetMonsterAnimInstance() { return animInst; }
	bool EnablePatrolPosArray() { return patrolPosArray.Num() > 0; }
	FVector GetPatrolPos() { return patrolPosArray[patrolPosIndex]; }
	void NextPatrolPosIndex() { patrolPosIndex = (patrolPosIndex + 1) % patrolPosArray.Num(); }
	void AddPatrolPos(const FVector& Pos) { patrolPosArray.Add(Pos); }
	void EnableDissolve();
	void SetProjectileDirection(const FVector& Direction) { projectileDir = Direction; }
	void SetLocomotion();
	void SetDodge();

	bool IsSkill() { return isSkill; }

	void Dead();
	void DropItem();

	void SetAIPatrolEnable();
	void SetSpawner(class AMonsterSpawner* Spawner);

	void EnableHUD(bool Enable);


	void SetAnimState(EMonsterAnimState AnimState);

public:
	virtual void NormalAttack();
	virtual void NormalStunAttack();
	virtual void NormalStaggerAttack();
	virtual void Attack();
	virtual void Ranged();
	virtual void Skill();
	virtual void UseSkill();
	virtual void Fire();
	virtual void Breath();

	virtual void FrontDodgeThrust();
	virtual void FrontDodge() {}
	virtual void Thrust() {}

	void DodgeCoolInit();
	bool DodgeReady() { return movement->DodgeReady(); }

	bool IsAttackDistance();
	virtual void AttackPattern() {}

	USkeletalMeshComponent* GetMesh() { return mesh; }
};
