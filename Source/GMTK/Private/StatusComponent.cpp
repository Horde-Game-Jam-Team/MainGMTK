#include "StatusComponent.h"
#include "Engine/Engine.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Health = MaxHealth;
}

void UStatusComponent::RestoreHealth(int32 Amount)
{
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
}

void UStatusComponent::TakeDamage(int32 Amount)
{
	Health -= Amount;

	if (Health <= 0)
		KillOwner();

	else
	{
		if (GEngine)
		{
			FString Message = FString::Printf(TEXT("%s is still alive"), *GetOwner()->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Message);
		}
	}
}

void UStatusComponent::KillOwner_Implementation()
{
	GetOwner()->Destroy();
}