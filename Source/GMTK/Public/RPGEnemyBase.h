// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "RPGAttributeSet.h"
#include "GameFramework/Character.h"
#include "RPGEnemyBase.generated.h"

UCLASS()
class GMTK_API ARPGEnemyBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ability system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, Replicated, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	// Attribute set
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attributes, Replicated, meta = (AllowPrivateAccess = "true"))
	URPGAttributeSet* AttributeSet;

	void InitializeAttributes();

public:
	
	//Implement interface method to return the ability system component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Blueprint event to handle health changes and update ui
	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* Attribute change handlers */

	// Health attributes
	void HandleHealthChanged(const FOnAttributeChangeData& Data);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
