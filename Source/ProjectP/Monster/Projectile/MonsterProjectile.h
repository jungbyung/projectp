// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../DefaultGameCommon.h"
#include "GameFramework/Actor.h"
#include "MonsterProjectile.generated.h"

UCLASS()
class PROJECTP_API AMonsterProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterProjectile();
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> body;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> movement;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> projectile;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystem> impactParticle;

	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UNiagaraSystem> nsSystem;
	//
	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UNiagaraComponent> nsProjectile;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USoundBase> impactSound;

	float limitDistance = 2000.f;
	int32 attack = 0.f;

	FVector prevLocation;
	bool computeDistance = false;

	AController* ownerController = nullptr;
	AActor* owner = nullptr;

	TObjectPtr<class ADecal> areaDecal;

	UPROPERTY()
	FVector targetLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION()
	void ProjectileStop(const FHitResult& Hit);
public:
	//void SetProjecttileSpeed()
	void SetLimitDistance(float dist) { limitDistance = dist; }
	void SetOwnerController(AController* Controller){ ownerController = Controller;	}
	void SetOwner(AActor* OwnerActor) { owner = OwnerActor;	}

public:

	void SetImpactParticle(const FString& Path);
	void SetImpactParticle(UParticleSystem* Particle);

	void SetImpactSound(const FString& Path);
	void SetImpactSound(USoundBase* Sound);

	void SetProjectileTargetLocation(const FVector& Target);
	FVector GetProjectileTargetLocation() { return targetLocation; }

	virtual void SetDecal();
};
