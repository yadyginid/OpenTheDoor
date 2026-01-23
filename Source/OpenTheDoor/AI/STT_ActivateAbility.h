// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STT_Base.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "STT_ActivateAbility.generated.h"

class UGameplayAbility;

UCLASS()
class OPENTHEDOOR_API USTT_ActivateAbility : public USTT_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="GAS")
	TSubclassOf<UGameplayAbility> AbilityClass;
	
	UPROPERTY(EditAnywhere, Category="GAS")
	bool bWaitAbilityEnd = true;

	UPROPERTY(EditAnywhere, Category="GAS")
	FGameplayTag AttackedTag;
	FTimerHandle IdleTimerHandle;

protected:
	UPROPERTY()
	UAbilitySystemComponent* ABS;

	FDelegateHandle AbilityEndedHandle;

	UFUNCTION()
	void OnFinishIdle();
	
	virtual void ExecuteTask() override;
	void OnAbilityEnded(const FAbilityEndedData& AbilityEndedData);
};
