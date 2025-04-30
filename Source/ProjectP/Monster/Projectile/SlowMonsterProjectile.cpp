// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowMonsterProjectile.h"
#include "../../Decal/Decal.h"
#include "../Monster.h"
#include "../../Player/PlayerCharacter.h"

ASlowMonsterProjectile::ASlowMonsterProjectile()
{
	movement->InitialSpeed = 500.f;
}

void ASlowMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ASlowMonsterProjectile::SetDecal()
{


	FVector dir = targetLocation - GetActorLocation();
	float Distance = FVector::Distance(targetLocation, GetActorLocation()) * 1.5f;
	dir = dir.GetSafeNormal();
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("begineplay"));

	TArray<FHitResult> Hits;


	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());

	bool collision = GetWorld()->LineTraceMultiByChannel(Hits, GetActorLocation(),
		GetActorLocation() + dir * Distance,
		ECollisionChannel::ECC_Visibility, Params); 

	if (collision)
	{
		for (FHitResult Hit : Hits)
		{
			AMonster* Monster = Cast<AMonster>(Hit.GetActor());
			APlayerCharacter* Player = Cast<APlayerCharacter>(Hit.GetActor());

			if (!Monster && !Player) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Red, FString::Printf(TEXT("hit actor %s"), *Hit.GetActor()->GetName()));
				DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + dir * Distance * 1.5f, FColor::Red, true, 5.f);
				FActorSpawnParameters param;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				
				areaDecal = GetWorld()->SpawnActor<ADecal>(Hit.ImpactPoint, FVector(90.f, 0.f, 0.f).Rotation(), param);
				
				areaDecal->SetDecalMaterial("/Script/Engine.Material'/Game/Material/M_DecalArea.M_DecalArea'");
				break;
			}
		}
	}


}
