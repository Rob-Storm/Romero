#include "ZombieSpawner.h"
#include "UObject/Object.h"
#include "TimerManager.h"

#include "Components/CapsuleComponent.h"

AZombieSpawner::AZombieSpawner()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	ArrowComponent->SetupAttachment(RootComponent);

	GetCapsuleComponent()->InitCapsuleSize(40.0f, 92.0f);
	GetCapsuleComponent()->SetShouldUpdatePhysicsVolume(false);

#if WITH_EDITORONLY_DATA

    static ConstructorHelpers::FObjectFinder<UTexture2D> Good(TEXT("/Game/Romero/Textures/Editor/ZombieSpawner.ZombieSpawner"));

    if (Good.Succeeded())
    {
        GetGoodSprite()->SetSprite(Good.Object);
        GetGoodSprite()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
    }

#endif

}

void AZombieSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnZombie();
}

void AZombieSpawner::SpawnZombie_Implementation()
{
    if (!HasAuthority())
    {
    	return;
    }

    UE_LOG(LogTemp, Error, TEXT("Attempting to spawn zombie"));

    UWorld* World = GetWorld();

    if (!World)
    {
        return;
    }

    FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ARomeroCharacter* SpawnedActor = GetWorld()->SpawnActor<ARomeroCharacter>
	(
		ZombieClass,
		GetActorLocation(), 
		GetActorRotation(), 
		SpawnParams
	);

	if(!SpawnedActor)
	{
		UE_LOG(LogTemp, Error, TEXT("Could not spawn zombie"));
		return;
	}

    SpawnedZombie = SpawnedActor;

    SpawnedActor->SetOwner(this);

	SpawnedZombie->HealthComponent->OnKilled.AddDynamic(this, &AZombieSpawner::OnZombieKilled);
}

void AZombieSpawner::OnZombieKilled()
{
	GetWorldTimerManager().SetTimer
	(
		RespawnTimerHandle,
		this,
		&AZombieSpawner::SpawnZombie,
		RespawnDelay,
		false
	);
}