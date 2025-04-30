// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "GameFramework/Actor.h"
#include "RangedSkill.generated.h"

UCLASS()
class PROJECTP_API ARangedSkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedSkill();
protected:
	TObjectPtr<USceneComponent> scene;
	TObjectPtr<class AMonsterAIController> aiController;
	TObjectPtr<AActor> owner;
	int32 spawnCount = 0;
	int32 spawnMaxCount = 0;

	float spawnTime = 0.5f;
	float spawnAccTime = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetMonsterAIController(class AMonsterAIController* Control);
	void SetSpawnCount(int32 Count) { spawnMaxCount = Count; }
	void SetOwnerActor(AActor* Actor);

};
