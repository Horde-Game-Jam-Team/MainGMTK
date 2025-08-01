#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.h"
#include "ItemDropComponent.generated.h"

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class GMTK_API UItemDropComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UItemDropComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TArray<TSubclassOf<AItem>> Items;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void SpawnItem();
};