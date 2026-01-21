// Copyright Epic Games, Inc. All Rights Reserved.

#include "ABaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "OpenTheDoor/GAS/CharacterAttributeSet.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ABaseCharacter::ABaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
}

void ABaseCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
	InitAbilitySystem();
}

void ABaseCharacter::InitAbilitySystem()
{
	if (AbilitySystemComp)
	{
		AbilitySystemComp->AddSet<UCharacterAttributeSet>();
		for (const TSubclassOf<UGameplayAbility>& GAClass : StartedAbilities)
		{
			FGameplayAbilitySpec GASpec = FGameplayAbilitySpec(GAClass);
			GASpec.SourceObject = this;
			AbilitySystemComp->GiveAbility(GASpec);
		}

		for (const TSubclassOf<UGameplayEffect>& GEClass : StartedGameplayEffects)
		{
			FGameplayEffectSpec GESpec = FGameplayEffectSpec(GEClass->GetDefaultObject<UGameplayEffect>(), AbilitySystemComp->MakeEffectContext());
			AbilitySystemComp->ApplyGameplayEffectSpecToSelf(GESpec);
		}
	}
}
