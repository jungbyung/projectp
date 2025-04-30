// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../defaultgameCommon.h"
#include "GameFramework/Actor.h"
#include <Components/SplineComponent.h>
#include "MonsterSpawner.generated.h"

UCLASS()
class PROJECTP_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawner();
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> patrolPath;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMonster> spawnMonsterClass;


	TObjectPtr<class AMonster> spawnMonster;

#if WITH_EDITORONLY_DATA
	/** Component shown in the editor only to indicate character facing */
	UPROPERTY()
	TObjectPtr<UArrowComponent> ArrowComponent;
#endif

	UPROPERTY(EditAnywhere)
	float spawnTime = 0.f;

	FTimerHandle spawnTimer;

	UPROPERTY(VisibleAnywhere)
	TArray<FVector> patrolPosArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void DestroySpawnMonster();

private:
	void SpawnTimer();
	void Spawn();
	

};
