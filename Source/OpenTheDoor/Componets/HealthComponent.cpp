// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "OpenTheDoor/Characters/ABaseCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	DeadTag = FGameplayTag::RequestGameplayTag("Effects.Dead");
}

void UHealthComponent::Init()
{
	if(const auto AbilityInterface = Cast<IAbilitySystemInterface>(GetOwner()))
	{
		ABS = AbilityInterface->GetAbilitySystemComponent();
		Binds();
	}
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::Binds()
{
	if (HealthChangedHandle.IsValid())
	{
		ABS->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthAttribute()).Remove(HealthChangedHandle);
		HealthChangedHandle.Reset();
	}

	HealthChangedHandle = ABS->GetGameplayAttributeValueChangeDelegate(UCharacterAttributeSet::GetHealthAttribute()).AddUObject(this, &UHealthComponent::OnHealthChanged);
}

void UHealthComponent::OnHealthChanged(const FOnAttributeChangeData& OnAttributeChangeData)
{
	const bool bDead = ABS->HasMatchingGameplayTag(DeadTag);
	if (OnAttributeChangeData.NewValue <= 0.f && !bDead){
		Dead();
	};
}

void UHealthComponent::Dead()
{
	if(!DeadAbility) return;
	ABS->TryActivateAbilityByClass(DeadAbility);
}

