// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerState.h"
#include "../GameMode/DefaultGameMode.h"
#include "DefaultPlayerController.h"

UDataTable* ADefaultPlayerState::stateData = nullptr;

ADefaultPlayerState::ADefaultPlayerState()
{
	if (!stateData)
	{
		static ConstructorHelpers::FObjectFinder<UDataTable>
			playerState(TEXT("/Script/Engine.DataTable'/Game/DataTables/DT_PlayerState.DT_PlayerState'"));

		if (playerState.Succeeded())
			stateData = playerState.Object;
	}
}

void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ADefaultGameMode* gameMode = GetWorld()->GetAuthGameMode<ADefaultGameMode>();

	if (IsValid(gameMode))
	{
		job = gameMode->GetPlayerJob();

		FPlayerStateData* data = stateData->FindRow<FPlayerStateData>(gameMode->GetPlayerJobName(), "");

		level = 1;
		exp = gold = 0;
		stamina = 500;
		staminaMax = 500;
		playerName = TEXT("Shinobi");

		if (data)
		{
			attackPower = data->attackPower;
			attackSpeed = data->attackSpeed;
			hp = data->hp;
			hpMax = data->hp;
			mp = data->mp;
			mpMax = data->mp;
			defense = data->defense;
			walkSpeed = data->walkSpeed;
			runSpeed = data->runSpeed;
			attackDistance = data->attackDistance;
			criticalHitChance = data->criticalHitChance;
			criticalHitRate = data->criticalHitRate;

			GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = walkSpeed;

			//ADefaultPlayerController* Controller = GetWorld()->GetFirstPlayerController<ADefaultPlayerController>();
			//if (IsValid(Controller))
			//{
			//	Controller->InitAttribute(*data);
			//}
			
		}

	}
}

void ADefaultPlayerState::OnConstruction(const FTransform& Transform)
{
}

void ADefaultPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultPlayerState::SetWalkAndRun(bool IsWalk)
{
	if(IsWalk)
		GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = runSpeed + moveSpeedPotion;
	else
		GetPawn<ACharacter>()->GetCharacterMovement()->MaxWalkSpeed = walkSpeed + moveSpeedPotion;

}

void ADefaultPlayerState::UseStamina(int32 UseStamina)
{
	stamina -= UseStamina;
	if (stamina <= 0) stamina = 0;
}
