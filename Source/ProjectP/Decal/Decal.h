// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../DefaultGameCommon.h"
#include "GameFramework/Actor.h"
#include "Decal.generated.h"

enum class EDecalFadeType
{
	None,
	FadeIn,
	FadeDuration,
	FadeOut
};
UCLASS()
class PROJECTP_API ADecal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADecal();
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> root;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDecalComponent> decal;

	TObjectPtr<UMaterialInstanceDynamic> decalMaterial;

	UPROPERTY(EditAnywhere)
	float fadeInTime = 0.f;
	UPROPERTY(EditAnywhere)
	float fadeDuration = 0.f;
	UPROPERTY(EditAnywhere)
	float fadeOutTime = 0.f;
	float fadeTime = 0.f;
	float fadeOpacity = 1.f;

	UPROPERTY(EditAnywhere)
	bool destroyAfterFade = true;;


	EDecalFadeType fadeType = EDecalFadeType::None;

public:
	void SetDecalMaterial(const FString& Path);
	void SetDecalMaterial(UMaterialInterface* Material);

	void SetDestroyAfterFade(bool AfterFade)
	{
		destroyAfterFade = AfterFade;
	}


	void SetDecalSize(const FVector& Size)
	{
		decal->DecalSize = Size;
	}

	void SetFadeDuration(float Time)
	{

		if (Time > 0.f)
			if (fadeType != EDecalFadeType::FadeIn)
				fadeType = EDecalFadeType::FadeDuration;
		fadeDuration = Time;
	}

	void SetFadeInTime(float Time)
	{
		if (Time > 0.f)
			fadeType = EDecalFadeType::FadeIn;
		fadeInTime = Time;
	}
	void SetFadeOutTime(float Time)
	{
		if (Time > 0.f)
			if (fadeType == EDecalFadeType::None)
				fadeType = EDecalFadeType::FadeOut;
		fadeOutTime = Time;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform);

};
