// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class GMTK_API AItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComponent;

public:
	AItem();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	void CollectItem();

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	virtual void CollectItem_Implementation();
};