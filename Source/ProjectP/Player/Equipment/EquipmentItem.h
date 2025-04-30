// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../defaultgamecommon.h"
#include "Components/scenecomponent.h"
#include "EquipmentItem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTP_API UEquipmentItem : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentItem();
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UWeaponComponent> weapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:

	void LoadWeapon(const FString& Path);
	void Init(class USkeletalMeshComponent* Mesh, const FName& Socket);
	void SetupWeaponAttachment(class USkeletalMeshComponent* Mesh, const FName& Socket);

	void UpdateGuard(EGuardState GuardState);


	class UWeaponComponent* GetWeaponComponent();
		
};
