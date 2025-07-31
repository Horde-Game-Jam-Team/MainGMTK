#include "ItemDropComponent.h"
#include "Components/SceneComponent.h"

UItemDropComponent::UItemDropComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UItemDropComponent::SpawnItem()
{
	if (Items.Num() == 0)
		return;

	int32 Index = FMath::RandRange(0, Items.Num() - 1);
	TSubclassOf<AItem> ItemClass = Items[Index];

	if (!ItemClass)
		return;

	FTransform NewTransform = GetOwner()->GetTransform();
	AItem* NewItem = GetWorld()->SpawnActor<AItem>(ItemClass, NewTransform);

	if (IsValid(NewItem))
		NewItem->FinishSpawning(NewTransform);
}