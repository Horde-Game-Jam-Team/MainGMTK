// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"	
#include "RPGAttributeSet.generated.h"


// Macro to easily declare attributes accessors
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class GMTK_API URPGAttributeSet : public UAttributeSet
{
    GENERATED_BODY()
public:
    // Constructor
    URPGAttributeSet();
    
    /*
        Attributes
    */
    // Health
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
    FGameplayAttributeData CurrentHealth;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, CurrentHealth)
    
    UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)
    
    // Resources
    UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_CurrentMana)
    FGameplayAttributeData CurrentMana;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, CurrentMana)
    
    UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_MaxMana)
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana)
    
    UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_CurrentStamina)
    FGameplayAttributeData CurrentStamina;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, CurrentStamina)

    UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_MaxStamina)
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxStamina)

    UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_FireCrystals)
    FGameplayAttributeData FireCrystals;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireCrystals)
    
    // Movement
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpeed)
    FGameplayAttributeData MovementSpeed;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MovementSpeed)
    
    UPROPERTY(BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MovementSpellHaste)
    FGameplayAttributeData MovementSpellHaste;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MovementSpellHaste)
    
    // Damage
    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_BaseDamage)
    FGameplayAttributeData BaseDamage;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, BaseDamage)
    
    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackSpeed)
    FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackSpeed)
    
    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_SpellDamageMultiplier)
    FGameplayAttributeData SpellDamageMultiplier;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, SpellDamageMultiplier)
    
    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AbilityHaste)
    FGameplayAttributeData AbilityHaste;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, AbilityHaste)
    
    UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_CastSpeed)
    FGameplayAttributeData CastSpeed;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, CastSpeed)
    
    // Armor
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_PhysicalArmor)
    FGameplayAttributeData PhysicalArmor;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalArmor)
    
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_MagicArmor)
    FGameplayAttributeData MagicArmor;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, MagicArmor)
    
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_Tenacity)
    FGameplayAttributeData Tenacity;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Tenacity)
    
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_DodgeChance)
    FGameplayAttributeData DodgeChance;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, DodgeChance)
    
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_PoisonResistance)
    FGameplayAttributeData PoisonResistance;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, PoisonResistance)
    
    UPROPERTY(BlueprintReadOnly, Category = "Armor", ReplicatedUsing = OnRep_FireResistance)
    FGameplayAttributeData FireResistance;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireResistance)

protected:
    // Replication notifies
    // Health
    UFUNCTION()
    void OnRep_CurrentHealth(const FGameplayAttributeData& OldCurrentHealth);
    
    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
    
    // Resources
    UFUNCTION()
    void OnRep_CurrentMana(const FGameplayAttributeData& OldCurrentMana);
    
    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

    UFUNCTION()
    void OnRep_CurrentStamina(const FGameplayAttributeData& OldCurrentStamina);

    UFUNCTION()
    void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);

    UFUNCTION()
    void OnRep_FireCrystals(const FGameplayAttributeData& OldFireCrystals);
    
    // Movement
    UFUNCTION()
    void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
    
    UFUNCTION()
    void OnRep_MovementSpellHaste(const FGameplayAttributeData& OldMovementSpellHaste);
    
    // Damage
    UFUNCTION()
    void OnRep_BaseDamage(const FGameplayAttributeData& OldBaseDamage);
    
    UFUNCTION()
    void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);
    
    UFUNCTION()
    void OnRep_SpellDamageMultiplier(const FGameplayAttributeData& OldSpellDamageMultiplier);
    
    UFUNCTION()
    void OnRep_AbilityHaste(const FGameplayAttributeData& OldAbilityHaste);
    
    UFUNCTION()
    void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed);
    
    // Armor
    UFUNCTION()
    void OnRep_PhysicalArmor(const FGameplayAttributeData& OldPhysicalArmor);
    
    UFUNCTION()
    void OnRep_MagicArmor(const FGameplayAttributeData& OldMagicArmor);
    
    UFUNCTION()
    void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity);
    
    UFUNCTION()
    void OnRep_DodgeChance(const FGameplayAttributeData& OldDodgeChance);
    
    UFUNCTION()
    void OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance);
    
    UFUNCTION()
    void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Attribute change handlers
    // This function is called before the attribute value is changed (for clamping, etc.)
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

    // This function is called after the attribute value has been changed (for applying effects, etc.)
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};