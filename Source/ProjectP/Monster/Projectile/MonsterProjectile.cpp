// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterProjectile.h"
#include "../../Decal/Decal.h"

// Sets default values
AMonsterProjectile::AMonsterProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<USphereComponent>(TEXT("body"));
	projectile = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("projectile"));
	//nsProjectile = CreateDefaultSubobject<UNiagaraComponent>(TEXT("pp"));
	SetRootComponent(body);

	projectile->SetupAttachment(body);
	//nsProjectile->SetupAttachment(body);

	body->SetCollisionProfileName(TEXT("MonsterProjectile"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem>
		Particle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonProps/FX/Particles/Core/P_SingleTargetCore_Projectile.P_SingleTargetCore_Projectile'"));

	if (Particle.Succeeded())
		projectile->Template = Particle.Object;

	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem>
	//	NSProjectile(TEXT("/Script/Niagara.NiagaraSystem'/Game/MixedVFX/Particles/Projectiles/NS_Projectile_01.NS_Projectile_01'"));
	//
	//if (NSProjectile.Succeeded())
	//	nsProjectile->SetAsset(NSProjectile.Object);
		//nsSystem = NSProjectile.Object;


	projectile->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));

	movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movement"));
	movement->SetUpdatedComponent(body);

	movement->InitialSpeed = 1000.f;
	movement->ProjectileGravityScale = 0.f;

	movement->OnProjectileStop.AddDynamic(this, &AMonsterProjectile::ProjectileStop);
}

// Called when the game starts or when spawned
void AMonsterProjectile::BeginPlay()
{
	Super::BeginPlay();

//	UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), GetActorLocation() + (-FVector::UpVector) * 2000.f,
// 		ECollisionChannel::ECC_Visibility,

	
}

// Called every frame
void AMonsterProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (computeDistance)
	{
		FVector Loc = GetActorLocation();

		float dist = FVector::Distance(prevLocation, Loc);

		limitDistance -= dist;

		if (limitDistance <= 0.f)
		{
			Destroy();
			return;
		}
	}
	else
		computeDistance = true;


	prevLocation = GetActorLocation();
}

void AMonsterProjectile::ProjectileStop(const FHitResult& Hit)
{

	FPointDamageEvent PointDamageEvent;

	PointDamageEvent.HitInfo = Hit;
	PointDamageEvent.DamageTypeClass = UNormalDamageType::StaticClass();

	float dmg = Hit.GetActor()->TakeDamage((float)attack, PointDamageEvent, ownerController, owner);


	UParticleSystem* particle = LoadObject<UParticleSystem>(GetWorld(),
		TEXT("/Script/Engine.ParticleSystem'/Game/ParagonProps/FX/Particles/Core/P_SingleTargetCore_MuzzleFlash.P_SingleTargetCore_MuzzleFlash'"));

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), particle, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	USoundBase* sound = LoadObject<USoundBase>(GetWorld(),
		TEXT("/Script/Engine.SoundWave'/Game/Sound/1/Explosion_Medium_2-1.Explosion_Medium_2-1'"));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), sound, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

	if (areaDecal)
	{
		areaDecal->Destroy();
		areaDecal = nullptr;
	}
	Destroy();
}

void AMonsterProjectile::SetImpactParticle(const FString& Path)
{
	UParticleSystem* particle = LoadObject<UParticleSystem>(this, *Path);

	if (IsValid(particle))
		impactParticle = particle;
}

void AMonsterProjectile::SetImpactParticle(UParticleSystem* Particle)
{
	if (IsValid(Particle))
		impactParticle = Particle;
}

void AMonsterProjectile::SetImpactSound(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(this, *Path);

	if (IsValid(Sound))
		impactSound = Sound;
}

void AMonsterProjectile::SetImpactSound(USoundBase* Sound)
{
	if (IsValid(Sound))
		impactSound = Sound;
}

void AMonsterProjectile::SetProjectileTargetLocation(const FVector& Target)
{
	targetLocation = Target;
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("settarget"));
}

void AMonsterProjectile::SetDecal()
{
}
