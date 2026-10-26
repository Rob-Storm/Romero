#include "Buildable/BuildableActor.h"
#include "UObject/Object.h"
#include "Net/UnrealNetwork.h"

ABuildableActor::ABuildableActor()
{
	bReplicates = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	StaticMeshComponent->SetIsReplicated(true);
	StaticMeshComponent->SetCanEverAffectNavigation(true);

	RootComponent = StaticMeshComponent;
}

void ABuildableActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABuildableActor::OnActorLoaded()
{
	OnRep_Model();
}

void ABuildableActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuildableActor, Model);
}


void ABuildableActor::OnRep_Model()
{
	StaticMeshComponent->SetStaticMesh(Model);
}