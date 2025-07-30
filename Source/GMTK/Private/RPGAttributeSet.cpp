// Fill out your copyright notice in the Description page of Project Settings.

#include "RPGAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

URPGAttributeSet::URPGAttributeSet()
    : CurrentHealth(100.f) // Default health value
    , MaxHealth(100.f) // Maximum health
    , CurrentMana(50.f) // Default mana value
    , MaxMana(50.f) // Maximum mana
    , CurrentStamina(75.f) // Default stamina value
    , MaxStamina(75.f) // Maximum stamina
    , MovementSpeed(600.f) // Default movement speed
    , MovementSpellHaste(1.f) // Default spell haste multiplier
    , BaseDamage(10.f) // Default base damage
    , AttackSpeed(1.f) // Default attack speed multiplier
    , SpellDamageMultiplier(1.f) // Default spell damage multiplier
    , AbilityHaste(0.f) // Default ability haste
    , CastSpeed(1.f) // Default cast speed multiplier
    , PhysicalArmor(5.f) // Default physical armor
    , MagicArmor(5.f) // Default magic armor
    , Tenacity(0.f) // Default tenacity
    , DodgeChance(5.f) // Default dodge chance
    , PoisonResistance(0.f) // Default poison resistance
    , FireResistance(0.f) // Default fire resistance
{
}

// Unfolded OnRep methods for Health attributes
void URPGAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CurrentHealth, OldCurrentHealth);
}

void URPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth, OldMaxHealth);
}

// Unfolded OnRep methods for Mana attributes
void URPGAttributeSet::OnRep_CurrentMana(const FGameplayAttributeData& OldCurrentMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CurrentMana, OldCurrentMana);
}

void URPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxMana, OldMaxMana);
}

// Unfolded OnRep methods for Stamina attributes
void URPGAttributeSet::OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CurrentStamina, OldCurrentStamina);
}

void URPGAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxStamina, OldMaxStamina);
}

// Unfolded OnRep methods for Movement attributes
void URPGAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MovementSpeed, OldMovementSpeed);
}

void URPGAttributeSet::OnRep_MovementSpellHaste(const FGameplayAttributeData& OldMovementSpellHaste)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MovementSpellHaste, OldMovementSpellHaste);
}

// Unfolded OnRep methods for Damage attributes
void URPGAttributeSet::OnRep_BaseDamage(const FGameplayAttributeData& OldBaseDamage)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, BaseDamage, OldBaseDamage);
}

void URPGAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AttackSpeed, OldAttackSpeed);
}

void URPGAttributeSet::OnRep_SpellDamageMultiplier(const FGameplayAttributeData& OldSpellDamageMultiplier)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, SpellDamageMultiplier, OldSpellDamageMultiplier);
}

void URPGAttributeSet::OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, AbilityHaste, OldAbilityHaste);
}

void URPGAttributeSet::OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CastSpeed, OldCastSpeed);
}

// Unfolded OnRep methods for Armor attributes
void URPGAttributeSet::OnRep_PhysicalArmor(const FGameplayAttributeData& OldPhysicalArmor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalArmor, OldPhysicalArmor);
}

void URPGAttributeSet::OnRep_MagicArmor(const FGameplayAttributeData& OldMagicArmor)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MagicArmor, OldMagicArmor);
}

void URPGAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Tenacity, OldTenacity);
}

void URPGAttributeSet::OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DodgeChance, OldDodgeChance);
}

void URPGAttributeSet::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PoisonResistance, OldPoisonResistance);
}

void URPGAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireResistance, OldFireResistance);
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Health attributes
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    
    // Mana attributes
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CurrentMana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
    
    // Movement attributes
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MovementSpellHaste, COND_None, REPNOTIFY_Always);
    
    // Damage attributes
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, BaseDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, SpellDamageMultiplier, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, AbilityHaste, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CastSpeed, COND_None, REPNOTIFY_Always);
    
    // Armor attributes
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, PhysicalArmor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MagicArmor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, DodgeChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, PoisonResistance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
}

//this function is called when the attribute is changed
void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    // Clamp the attribute values to their maximum limits
    if (Attribute == GetCurrentHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, MaxHealth.GetCurrentValue());
    }
    else if (Attribute == GetCurrentManaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, MaxMana.GetCurrentValue());
    }
    else if (Attribute == GetCurrentStaminaAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.f, MaxStamina.GetCurrentValue());
    }
}

// this function is called after the attribute value is changed
void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    // Handle any post-execution logic here, such as applying damage or healing

    
    if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
    {
        //Re-clamp the current health to ensure it doesn't exceed max health or drop below 0
        SetCurrentHealth(FMath::Clamp(CurrentHealth.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));

        // Example: If health drops to 0, trigger death logic
        if (CurrentHealth.GetCurrentValue() <= 0.f)
        {
            // Handle character death logic here
        }
    }

    // Handle mana and stamina similarly
    // Re-clamp the current mana and stamina to ensure they don't exceed max values or drop below 0
    if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
    {
        SetCurrentMana(FMath::Clamp(CurrentMana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
    }

    if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
    {
        SetCurrentStamina(FMath::Clamp(CurrentStamina.GetCurrentValue(), 0.f, MaxStamina.GetCurrentValue()));
    }
}