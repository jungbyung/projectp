// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "../UI/Main/MainWidget.h"
#include "PlayerCharacter.h"
#include "DefaultPlayerState.h"
#include "../Item/ItemBase.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;


	static ConstructorHelpers::FClassFinder<UUserWidget>
		MainWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/Main/WB_MainWidget.WB_MainWidget_C'"));

	if (MainWidgetClass.Succeeded())
	{
		mainWidgetClass = MainWidgetClass.Class;
	}


}

UMainWidget* ADefaultPlayerController::GetMainWidget() const
{
	return mainWidget;
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(mainWidgetClass))
	{
		mainWidget = CreateWidget<UMainWidget>(GetWorld(),
			mainWidgetClass, TEXT("UI_Main"));

		if (IsValid(mainWidget))
		{
			//mainWidget->SetInventoryOwnerActor(GetPawn());
			mainWidget->SetWidgetOwnerActor(GetPawn());
			mainWidget->InitWidget();
			mainWidget->AddToViewport();

			//mainWidget->SetIsEnabled(false);
		}
	}
}

void ADefaultPlayerController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ADefaultPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADefaultPlayerController::SetPlayerRenderTarget(UTexture2D* Texture)
{
	mainWidget->SetPlayerRenderTarget(Texture);
}

void ADefaultPlayerController::SetHPRatio(float HPRatio)
{
	mainWidget->SetHPRatio(HPRatio);

}

void ADefaultPlayerController::SetStaminaRatio(float StaminaRatio)
{
	mainWidget->SetStaminaRatio(StaminaRatio);
}

void ADefaultPlayerController::SetSkillCoolTime(int32 Index, float Ratio)
{
	mainWidget->SetSkillCoolTime(Index, Ratio);
}

void ADefaultPlayerController::SkillCoolTimeEnd(int32 Index)
{
	mainWidget->SkillCoolTimeEnd(Index);
}

void ADefaultPlayerController::SetItemInfo(UItemBase* Data, bool Visible)
{
	mainWidget->SetItemInfo(Data, Visible);
}

void ADefaultPlayerController::SetSkillInfo(USkillBase* Skill, bool Visible)
{
	mainWidget->SetSkillInfo(Skill, Visible);
}

void ADefaultPlayerController::ShowMouseCursor()
{
	if (mainWidget->IsInventory() ||
		mainWidget->IsAttribute())
	{
		bShowMouseCursor = true;
		SetIgnoreLookInput(true);
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		bShowMouseCursor = false;
		//SetIgnoreLookInput(false);
		ResetIgnoreLookInput();
		SetInputMode(FInputModeGameOnly());
	}
}

void ADefaultPlayerController::ToggleInventory()
{
	mainWidget->ToggleInventory();
	ShowMouseCursor();
	
	USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
		TEXT("/Script/Engine.SoundWave'/Game/Free_Sounds_Pack/wav/Interface_1-1.Interface_1-1'"));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, GetPawn()->GetActorLocation(), GetPawn()->GetActorRotation());
}

void ADefaultPlayerController::ToggleAttribute()
{
	mainWidget->ToggleAttribute();
	ShowMouseCursor();
	USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
		TEXT("/Script/Engine.SoundWave'/Game/Free_Sounds_Pack/wav/Interface_1-1.Interface_1-1'"));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, GetPawn()->GetActorLocation(), GetPawn()->GetActorRotation());

}

void ADefaultPlayerController::AddBuffItem(class UItemBase* Data)
{
	mainWidget->AddBuffItem(Data);
}

void ADefaultPlayerController::InitAttribute()
{
	//mainWidget->InitAttribute(State);

	APlayerCharacter* Shinobi = GetPawn<APlayerCharacter>();

	if (IsValid(Shinobi))
	{

		mainWidget->SetAttributeJob(TEXT("Shinobi"));
		mainWidget->SetAttributeHP(Shinobi->GetDefaultPlayerState()->GetHP(), Shinobi->GetDefaultPlayerState()->GetHPMax());
		mainWidget->SetAttributeStemina(Shinobi->GetDefaultPlayerState()->GetStamina(), Shinobi->GetDefaultPlayerState()->GetStaminaMax());
		mainWidget->SetAttributeAttackPower(Shinobi->GetDefaultPlayerState()->GetAttackPower());
		mainWidget->SetAttributeDefense(Shinobi->GetDefaultPlayerState()->GetDefense());
		mainWidget->SetAttributeAttackSpeed(Shinobi->GetDefaultPlayerState()->GetAttackSpeed());
		mainWidget->SetAttributeMoveSpeed(Shinobi->GetMovementComponent()->GetMaxSpeed());

	}
}

void ADefaultPlayerController::SetAttributeJob(const FString& Job)
{
	mainWidget->SetAttributeJob(Job);
}

void ADefaultPlayerController::SetAttributeHP(int32 HP, int32 HPMax)
{
	mainWidget->SetAttributeHP(HP, HPMax);
}

void ADefaultPlayerController::SetAttributeStemina(int32 Stemina, int32 SteminaMax)
{
	mainWidget->SetAttributeStemina(Stemina, SteminaMax);
}

void ADefaultPlayerController::SetAttributeAttackPower(int32 AttackPower)
{
	mainWidget->SetAttributeAttackPower(AttackPower);
}

void ADefaultPlayerController::SetAttributeDefense(int32 Defense)
{
	mainWidget->SetAttributeDefense(Defense);
}

void ADefaultPlayerController::SetAttributeAttackSpeed(float AttackSpeed)
{
	mainWidget->SetAttributeAttackSpeed(AttackSpeed);
}

void ADefaultPlayerController::SetAttributeMoveSpeed(float MoveSpeed)
{
	mainWidget->SetAttributeMoveSpeed(MoveSpeed);
}

