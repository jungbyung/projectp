// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "Components/ActorComponent.h"
#include "MonsterStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UMonsterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStateComponent();

protected:
	static UDataTable* stateData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName monsterRowName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMonsterGrade grade;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 attackPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float attackSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 hp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 hpMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 mp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 mpMax;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 defense;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 exp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 gold;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float walkSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float runSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float attackDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float criticalHitChance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float criticalHitRate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	int32 GetAttackPower() { return attackPower; }
	float GetCriticalHitChance() { return criticalHitChance; }
	float GetCriticalHitRate() { return criticalHitRate; }
	float GetAttackDistance() { return attackDistance; }
	float GetAttackSpeed() { return attackSpeed; }
	float GetWalkSpeed() { return walkSpeed; }
	float GetRunSpeed() { return runSpeed; }
	int32 GetHP() { return hp; }
	int32 GetHPMax() { return hpMax; }
	int32 GetMP() { return mp; }
	int32 GetMPMax() { return mpMax; }
	int32 GetLevel() { return level; }
	int32 GetGold() { return gold; }
	int32 GetExp() { return exp; }
	int32 GetDefense() { return defense; }
	FString GetName() { return name; }
	FName GetRowName() { return monsterRowName; }
	EMonsterGrade GetGrade() { return grade; }

	void SetMonsterRowName(FName RowName) { monsterRowName = RowName; }
	void SetAttackPower(int32 AttackPower) { attackPower = AttackPower; }
	void SetHP(int32 HP) { hp = HP; }
	void SetHPMax(int32 HPMax) { hpMax = HPMax; }
	void SetMP(int32 MP) { mp = MP; }
	void SetMPMax(int32 MPMax) { mpMax = MPMax; }
	void SetLevel(int32 Level) { level = Level; }
	void SetGold(int32 Gold) { gold = Gold; }
	void SetExp(int32 Exp) { exp = Exp; }
	void SetDefense(int32 Defense) { defense = Defense; }
	void SetAttackDistance(float AttackDistance) { attackDistance = AttackDistance; }
	void SetAttackSpeed(float AttackSpeed) { attackSpeed = AttackSpeed; }
	void SetCriticalHitChance(float CriticalHitChance) { criticalHitChance = CriticalHitChance; }
	void SetCriticalHitRate(float CriticalHitRate) { criticalHitRate = CriticalHitRate; }

	void AddHP(int32 HP) { hp += HP; }
};
