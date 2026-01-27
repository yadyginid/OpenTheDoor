// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENTHEDOOR_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbility> DeadAbility;

	void Init();

protected:
	UPROPERTY()
	UAbilitySystemComponent* ABS;
	
	FGameplayTag DeadTag;
	FDelegateHandle HealthChangedHandle;
	
	virtual void BeginPlay() override;
	
	void Binds();
	void OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData);

	void Dead();
};
