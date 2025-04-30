// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedSkill.h"
#include "../AI/MonsterAIController.h"
#include "../Projectile/MonsterProjectile.h"
#include "../Projectile/SlowMonsterProjectile.h"
#include "../Monster.h"

// Sets default values
ARangedSkill::ARangedSkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scene = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));

	SetRootComponent(scene);
}

// Called when the game starts or when spawned
void ARangedSkill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangedSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spawnAccTime += DeltaTime;

	if (spawnAccTime >= spawnTime)
	{
		spawnAccTime = 0;

		if (IsValid(aiController->GetTarget()))
		{
			AMonster* Monster = Cast<AMonster>(owner);

			if (Monster)
			{
				FVector center = Monster->GetMesh()->GetSocketLocation(TEXT("Fire"));

				//FVector center = GetActorLocation();

				FActorSpawnParameters Param;
				Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				FVector TargetLocation = aiController->GetTarget()->GetActorLocation();
				FRotator NewRot = GetTargetRotator(center, TargetLocation);

				ASlowMonsterProjectile* Projecttile =
					GetWorld()->SpawnActor<ASlowMonsterProjectile>(center, NewRot, Param);

				Projecttile->SetProjectileTargetLocation(TargetLocation);
				Projecttile->SetOwnerController(aiController);
				Projecttile->SetOwner(this);
				Projecttile->SetDecal();
				spawnCount++;
			}
		}

		if (spawnCount >= spawnMaxCount)
			Destroy();
	}

}

void ARangedSkill::SetMonsterAIController(AMonsterAIController* Control)
{
	aiController = Control;
}

void ARangedSkill::SetOwnerActor(AActor* Actor)
{
	owner = Actor;
}

