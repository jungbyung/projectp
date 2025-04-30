// Fill out your copyright notice in the Description page of Project Settings.


#include "Decal.h"

// Sets default values
ADecal::ADecal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	decal = CreateDefaultSubobject<UDecalComponent>(TEXT("decal"));

	SetRootComponent(root);

	decal->SetupAttachment(root);

	//root->bVisualizeComponent = true;

	decal->SetWorldRotation(FRotator(90.f, 0.f, 0.f));
	decal->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	//SetActorRotation(FRotator(0.f, 90.f, 0.f));

}

void ADecal::SetDecalMaterial(const FString& Path) 
{
	UMaterialInterface* Material = LoadObject< UMaterialInterface>(this, *Path);


	if (IsValid(Material))
	{
		decalMaterial = UMaterialInstanceDynamic::Create(Material, this);
		decal->SetDecalMaterial(decalMaterial);
	}
}

void ADecal::SetDecalMaterial(UMaterialInterface* Material)
{
	if (IsValid(Material))
	{
		decalMaterial = UMaterialInstanceDynamic::Create(Material, this);
		decal->SetDecalMaterial(decalMaterial);
	}
}

// Called when the game starts or when spawned
void ADecal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADecal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (fadeType)
	{
	case EDecalFadeType::FadeIn:
	{
		fadeTime += DeltaTime;

		fadeOpacity = fadeTime / fadeInTime;

		decalMaterial->SetScalarParameterValue(TEXT("Opacity"), fadeOpacity);

		if (fadeTime >= fadeInTime)
		{
			fadeTime = 0.f;
			fadeType = EDecalFadeType::FadeDuration;
		}
	}
	break;
	case EDecalFadeType::FadeDuration:
	{
		if (fadeDuration > 0.f)
		{
			fadeTime += DeltaTime;
			if (fadeTime >= fadeDuration)
			{
				fadeTime = 0.f;
				fadeType = EDecalFadeType::FadeOut;
			}
		}
		else
			fadeType = EDecalFadeType::FadeOut;
	}
	break;
	case EDecalFadeType::FadeOut:
	{
		if (fadeOutTime > 0.f)
		{

			fadeTime += DeltaTime;

			fadeOpacity = 1.f - fadeTime / fadeOutTime;

			decalMaterial->SetScalarParameterValue(TEXT("Opacity"), fadeOpacity);

			if (fadeTime >= fadeOutTime)
			{
				fadeTime = 0.f;
				if (destroyAfterFade)
				{
					Destroy();
				}
			}
		}
		else if (destroyAfterFade)
		{
			Destroy();
		}
	}
	break;
	default:
		break;
	}

}

void ADecal::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (fadeInTime > 0.f)
	{
		fadeType = EDecalFadeType::FadeIn;
	}
	else if (fadeDuration > 0.f)
	{
		fadeType = EDecalFadeType::FadeDuration;
	}
	else if (fadeOutTime > 0.f)
	{
		fadeType = EDecalFadeType::FadeOut;
	}
	else
		fadeType = EDecalFadeType::None;

	if (!IsValid(decalMaterial))
	{
		UMaterialInterface* decalMat = decal->GetDecalMaterial();

		if (IsValid(decalMat))
		{
			decalMaterial = UMaterialInstanceDynamic::Create(decalMat, this);
			decal->SetDecalMaterial(decalMaterial);
		}
	}
	else
	{
		UMaterialInterface* decalMat = decal->GetDecalMaterial();

		if (decalMaterial != decalMat)
		{
			decal->SetDecalMaterial(decalMat);
		}
	}
}


