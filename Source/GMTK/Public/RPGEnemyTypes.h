#pragma once

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Chasing     UMETA(DisplayName = "Chasing"),
	Attacking   UMETA(DisplayName = "Attacking"),
};
