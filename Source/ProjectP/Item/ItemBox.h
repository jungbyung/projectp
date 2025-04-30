// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "GameFramework/Actor.h"
#include "ItemBox.generated.h"

UCLASS()
class PROJECTP_API AItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBox();
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent>	box;

	//UPROPERTY(VisibleAnywhere)
	//TObjectPtr<UStaticMeshComponent>	mesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<URotatingMovementComponent> rotMovement;

	TObjectPtr<UNiagaraComponent> niagaraComp;

	UPROPERTY(EditAnywhere)
	FString		itemName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents();
private:

	UFUNCTION()
	void BoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void SetItemName(const FString& ItemName) { itemName = ItemName; }
	void RandItem();
};
