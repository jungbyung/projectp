// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "GameFramework/PlayerState.h"
#include "DefaultPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTP_API ADefaultPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	ADefaultPlayerState();
protected:

	static UDataTable* stateData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString playerName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerJob job;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 stamina;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 staminaMax;

	int32 attackPowerPotion = 0;
	int32 defensePotion = 0;
	float moveSpeedPotion = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void Tick(float DeltaTime) override;

public:
	void SetWalkAndRun(bool IsWalk);

public:
	int32 GetAttackPower() { return attackPower + attackPowerPotion; }
	float GetCriticalHitChance() { return criticalHitChance; }
	float GetCriticalHitRate() { return criticalHitRate; }
	float GetAttackDistance() { return attackDistance; }
	float GetAttackSpeed() { return attackSpeed; }
	int32 GetHP() { return hp; }
	int32 GetHPMax() { return hpMax; }
	int32 GetMP() { return mp; }
	int32 GetMPMax() { return mpMax; }
	int32 GetLevel() { return level; }
	int32 GetGold() { return gold; }
	int32 GetExp() { return exp; }
	int32 GetDefense() { return defense + defensePotion; }
	int32 GetStamina() { return stamina; }
	int32 GetStaminaMax() { return staminaMax; }

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
	void AddHP(int32 AddHP) { hp += AddHP; if (hp > hpMax) hp = hpMax; }
	bool IsDead() { return hp <= 0; }
	void SetStamina(int32 Stamina) { stamina = Stamina; }
	void AddStamina(int32 AddStamina) { stamina += AddStamina; if (stamina > staminaMax) stamina = staminaMax; }
	void UseStamina(int32 UseStamina);
	void SetAttackPowerUp(int32 AttackPowerUp) { attackPowerPotion = AttackPowerUp; }
	void SetDefenseUp(int32 DefensePotion) { defensePotion = DefensePotion; }
	void SetMoveSpeedUp(float MoveSpeedPotion) { moveSpeedPotion = MoveSpeedPotion; }

};
