#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent))
class GMTK_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatusComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status", meta = (ClampMin = "1", ClampMax = "99", UIMin = "1", UIMax = "99"))
	int32 MaxHealth;

	UFUNCTION(BlueprintCallable)
	void RestoreHealth(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void TakeDamage(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void KillOwner();
};