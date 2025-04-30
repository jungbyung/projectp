// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"
#include "WeaponComponent.h"
#include "components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UEquipmentItem::UEquipmentItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("weaponComp"));
	weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}


// Called when the game starts
void UEquipmentItem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentItem::LoadWeapon(const FString& Path)
{
	USkeletalMesh* WeaponMesh = LoadObject<USkeletalMesh>(nullptr, *Path);

	if (WeaponMesh)
		weapon->SetSkeletalMesh(WeaponMesh);
}

void UEquipmentItem::Init(USkeletalMeshComponent* Mesh, const FName& Socket)
{
	weapon->SetupAttachment(Mesh, Socket);
}

void UEquipmentItem::SetupWeaponAttachment(USkeletalMeshComponent* Mesh, const FName& Socket)
{
	if (weapon)
	{
		weapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, Socket);
	}
}

void UEquipmentItem::UpdateGuard(EGuardState GuardState)
{
	weapon->UpdateGuard(GuardState);
}

UWeaponComponent* UEquipmentItem::GetWeaponComponent()
{
	return weapon;
}

