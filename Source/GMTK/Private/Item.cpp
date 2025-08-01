#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RPGCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(60.f);
	RootComponent = CollisionComponent;
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnOverlapBegin);
}

void AItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARPGCharacter>(OtherActor))
	{
		CollectItem_Implementation();
		Destroy(); // Can be placed elsewhere, in case you don't want a specific item to be destroyed.
	}
}

void AItem::CollectItem_Implementation()
{
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("Item collected"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, Message);
	}
}