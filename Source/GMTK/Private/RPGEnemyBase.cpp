// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyBase.h"

#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"


// Sets default values
ARPGEnemyBase::ARPGEnemyBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Initialize the ability system component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	//Initialize the attribute set
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ARPGEnemyBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ARPGEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttributes();
	
}

// Called every frame
void ARPGEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPGEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARPGEnemyBase::InitializeAttributes()
{
	if (AbilitySystemComponent && AttributeSet)
	{
		// Bind to health change event
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &ARPGEnemyBase::HandleHealthChanged);

		}
}

// Function to handle health changes and update UI
void ARPGEnemyBase::HandleHealthChanged(const FOnAttributeChangeData& Data)
{
	// Handle health change logic here, such as updating UI or triggering events
	float NewHealth = Data.NewValue;
	float OldHealth = Data.OldValue;
	float DeltaHealth = NewHealth - OldHealth;

	// Call the Blueprint function to update UI
	OnHealthChanged(DeltaHealth, FGameplayTagContainer());
}

void ARPGEnemyBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARPGEnemyBase, AbilitySystemComponent);
	DOREPLIFETIME(ARPGEnemyBase, AttributeSet);
}

