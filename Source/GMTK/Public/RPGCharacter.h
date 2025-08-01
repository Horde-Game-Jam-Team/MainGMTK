// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "GenericTeamAgentInterface.h"
#include "RPGAttributeSet.h"
#include "RPGCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplatedCharacter, Log, All);

// Dispatcher for when don't fall behind occur
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFallBehindPunish);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class ARPGCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	class UInputAction* MouseLookAction;

	
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
	ARPGCharacter();

	
	//Implement interface method to return the ability system component
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	//Blueprint event to handle health changes and update ui
	UFUNCTION(BlueprintImplementableEvent, Category = "Health")
	void OnHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags);

	//Blueprint event to handle MovementSpeed changes and update ui
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void OnMovementSpeedChanged(float DeltaValue, const FGameplayTagContainer& EventTags);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	float UpperBodyPitch{0};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clavicle Control")
	float MinPitch = -60.f; // Looking down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Clavicle Control")
	float MaxPitch = 60.f;  // Looking up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield System")
	bool IsBlocking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shield System")
	bool ShieldPickedUp = false;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FOnFallBehindPunish OnFallBehindPunish;



protected:

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

	// Makes the player the enemy
	FGenericTeamId TeamId;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }



public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

private:

	/* Attribute change handlers */

	// Health attributes
	void HandleHealthChanged(const FOnAttributeChangeData& Data);

	//Movement attributes
	void HandleMovementSpeedChanged(const FOnAttributeChangeData& Data);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

