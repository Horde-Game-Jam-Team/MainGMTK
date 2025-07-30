// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Logging/LogMacros.h"
#include "RPGAttributeSet.h"
#include "RPGCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS()
class GMTK_API ARPGCharacter :  public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	
	// Sets default values for this character's properties
	ARPGCharacter();

	//Implement interface method to return the ability system component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Blueprint event to handle health changes and update ui
	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	//Blueprint event to handle Resource changes and update ui
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void OnManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void OnStaminaChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Resources")
	void OnFireCrystalsChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	//Blueprint event to handle MovementSpeed changes and update character speed
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void OnMovementSpeedChanged(float DeltaValue, const FGameplayTagContainer& EventTags);




protected:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	class UInputAction* MouseLookAction;

	
	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	
	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

	
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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:
	/* Attribute change handlers */

	// Health attributes
	void HandleHealthChanged(const FOnAttributeChangeData& Data);

	//Resources attributes
	void HandleManaChanged(const FOnAttributeChangeData& Data);
	void HandleStaminaChanged(const FOnAttributeChangeData& Data);
	void HandleFireCrystalsChanged(const FOnAttributeChangeData& Data);


	//Movement attributes
	void HandleMovementSpeedChanged(const FOnAttributeChangeData& Data);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
