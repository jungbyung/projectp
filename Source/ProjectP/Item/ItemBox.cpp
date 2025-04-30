// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "../Player/Inventory/InventoryInterface.h"
#include "../player/Inventory/InventoryComponent.h"
#include "ItemManager.h"
#include "ItemBase.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	rotMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("rot"));
	niagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("niagara"));

	SetRootComponent(box);

	//mesh->SetupAttachment(box);
	rotMovement->SetUpdatedComponent(box);
	niagaraComp->SetupAttachment(box);

	//static ConstructorHelpers::FObjectFinder<UStaticMesh>
	//	Mesh(TEXT("/Script/Engine.StaticMesh'/Game/sA_PickupSet_1/Models/SM_Pickup_Health.SM_Pickup_Health'"));
	//
	//if (Mesh.Succeeded())
	//	mesh->SetStaticMesh(Mesh.Object);

	//mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	box->SetBoxExtent(FVector(50.f, 50.f, 50.f));

	box->SetCollisionProfileName(TEXT("ItemBox"));


	rotMovement->RotationRate.Yaw = 180.f;



}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	box->OnComponentHit.AddDynamic(this, &AItemBox::BoxHit);
	box->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::BoxBeginOverlap);
	box->OnComponentEndOverlap.AddDynamic(this, &AItemBox::BoxEndOverlap);

}

void AItemBox::BoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(ProjectP, Warning, TEXT("BoxHit"));
}

void AItemBox::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(ProjectP, Warning, TEXT("BoxBeginOverlap"));

	IInventoryInterface* InvenInterface = Cast<IInventoryInterface>(OtherActor);

	if (InvenInterface)
	{
		UInventoryComponent* Inven = InvenInterface->GetInventoryComponent();

		if (IsValid(Inven))
		{
			Inven->AddItem(itemName);

			USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
				TEXT("/Script/Engine.SoundWave'/Game/Sound/3/item-pick-up-38258.item-pick-up-38258'"));

			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, GetActorLocation(), GetActorRotation());
			Destroy();
		}
	}

}

void AItemBox::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(ProjectP, Warning, TEXT("BoxEndOverlap"));
}

void AItemBox::RandItem()
{
	int32 i = FMath::Rand() % 4;

	switch (i)
	{
	case 0:
		itemName = TEXT("DefensePotion");
		break;
	case 1:
		itemName = TEXT("LifePotion");
		break;
	case 2:
		itemName = TEXT("PowerPotion");
		break;
	case 3:
		itemName = TEXT("StaminaPotion");
		break;
	default:
		break;
	}

	UItemBase* ItemBase = CItemManager::GetInstance()->GetItem(itemName);

	if (ItemBase)
	{
		if (ItemBase->GetNiagara().Num() > 0)
		{
			niagaraComp->SetAsset(ItemBase->GetNiagara()[0]);
		}
	}
}

