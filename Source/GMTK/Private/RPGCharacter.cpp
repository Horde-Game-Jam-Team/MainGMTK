// Copyright Epic Games, Inc. All Rights Reserved.

#include "RPGCharacter.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplatedCharacter);

//////////////////////////////////////////////////////////////////////////
// AGMTKCharacter

ARPGCharacter::ARPGCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Initialize the ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//Initialize the attribute set
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));

	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;

	TeamId = FGenericTeamId(1);
}

void ARPGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARPGCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARPGCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARPGCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ARPGCharacter::LookInput);
	}
	else
	{
		UE_LOG(LogTemplatedCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ARPGCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ARPGCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ARPGCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ARPGCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ARPGCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ARPGCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}



UAbilitySystemComponent* ARPGCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeAttributes();


}

void ARPGCharacter::InitializeAttributes()
{
	if (AbilitySystemComponent && AttributeSet)
	{
		// Bind to health change event
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &ARPGCharacter::HandleHealthChanged);

		//Bind to Movespeed change event
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMovementSpeedAttribute()).AddUObject(this, &ARPGCharacter::HandleMovementSpeedChanged);
	}
}

// Function to handle health changes and update UI
void ARPGCharacter::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	// Handle health change logic here, such as updating UI or triggering events
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;
	float DeltaHealth = NewHealth - OldHealth;

	// Call the Blueprint function to update UI
	OnHealthChanged(DeltaHealth, FGameplayTagContainer());
}

void ARPGCharacter::HandleMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	// Handle movement speed logic here, such as updating UI or triggering events
	float NewMovementSpeed = Data.NewValue;
	float OldMovementSpeed = Data.OldValue;
	float DeltaMovementSpeed = NewMovementSpeed - OldMovementSpeed;

	// Call the Blueprint function to update UI
	OnMovementSpeedChanged(DeltaMovementSpeed, FGameplayTagContainer());
}

void ARPGCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARPGCharacter, AbilitySystemComponent);
	DOREPLIFETIME(ARPGCharacter, AttributeSet);
}

// Called every frame
void ARPGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

