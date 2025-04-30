// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include "Monster.h"

// Sets default values
AMonsterSpawner::AMonsterSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));
	patrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("patrolPath"));

	SetRootComponent(root);
	patrolPath->SetupAttachment(root);

	patrolPath->SetClosedLoop(true);
	patrolPath->bDrawDebug = true;

#if WITH_EDITORONLY_DATA
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		//ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Characters;
		//ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Characters;
		ArrowComponent->SetupAttachment(root);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
#endif // WITH_EDITORONLY_DATA

	//root->bVisualizeComponent = true;

}

// Called when the game starts or when spawned
void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	int32 count = patrolPath->GetNumberOfSplinePoints();

	for (int32 i = 0; i < count; ++i)
	{
		FVector pos = patrolPath->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		patrolPosArray.Add(pos);
	}
	
	Spawn();
}

// Called every frame
void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (spawnMonster == nullptr &&
		spawnTime <= 0.f)
		Spawn();
}

void AMonsterSpawner::DestroySpawnMonster()
{
	spawnMonster = nullptr;

	if (spawnTime > 0.f)
		GetWorldTimerManager().SetTimer(spawnTimer, this, &AMonsterSpawner::SpawnTimer, spawnTime);
}

void AMonsterSpawner::SpawnTimer()
{
	GetWorldTimerManager().ClearTimer(spawnTimer);
	Spawn();
}

void AMonsterSpawner::Spawn()
{
	if (IsValid(spawnMonsterClass))
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		FVector spawnLocation = GetActorLocation();
		AMonster* cdo = spawnMonsterClass->GetDefaultObject<AMonster>();

		if (IsValid(cdo))
		{
			UCapsuleComponent* capsule = cdo->GetCapsule();
			spawnLocation.Z += capsule->GetScaledCapsuleRadius();
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("locationZ %f"), spawnLocation.Z));
		}
		spawnMonster = GetWorld()->SpawnActor<AMonster>(spawnMonsterClass, spawnLocation, GetActorRotation(), param);
		spawnMonster->SetSpawner(this);


		if (patrolPosArray.Num() > 0)
		{
			for (int32 i = 0; i < patrolPosArray.Num(); ++i)
			{
				spawnMonster->AddPatrolPos(patrolPosArray[i]);
			}
			//spawnMonster->SetAIPatrolEnable();
		}

	}
}

