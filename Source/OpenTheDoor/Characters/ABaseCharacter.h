// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "ABaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override {return AbilitySystemComp;}

protected:
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartedAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartedGameplayEffects;
	
	virtual void NotifyControllerChanged() override;
	virtual void InitAbilitySystem();
};

