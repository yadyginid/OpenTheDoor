// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_ActivateAbility.h"

#include "BaseAIController.h"
#include "OpenTheDoor/Characters/AICharacter.h"

void USTT_ActivateAbility::OnFinishIdle()
{
	FinishTask();
}

void USTT_ActivateAbility::ExecuteTask()
{
	FStateTreeEvent Event;
	Event.Tag = AttackedTag;
	
	ABS = AICharacter->GetAbilitySystemComponent();
	if(!AbilityClass || !ABS)
	{
		FinishTask();
		return;
	}

	if(bWaitAbilityEnd)
	{
		ABS->OnAbilityEnded.Remove(AbilityEndedHandle);
		AbilityEndedHandle = ABS->OnAbilityEnded.AddUObject(this, &USTT_ActivateAbility::OnAbilityEnded);
	}
	
	const bool bActivated = ABS->TryActivateAbilityByClass(AbilityClass);
	if(!bActivated)
	{
		UE_LOG(LogTemp, Warning, TEXT("USTT_ActivateAbility::ExecuteTask Cant' Activate ability by class %s"), *AbilityClass->GetName());
		FinishTask();
		return;
	}
	
	if(!bWaitAbilityEnd)
	{
		BaseAIController->StateTreeAIComponent->SendStateTreeEvent(Event);
		return;
	}
}

void USTT_ActivateAbility::OnAbilityEnded(const FAbilityEndedData& AbilityEndedData)
{
	if (!AbilityEndedData.AbilityThatEnded) return;
	if (AbilityEndedData.AbilityThatEnded->GetClass() != AbilityClass) return;
	
	FStateTreeEvent Event;
	Event.Tag = AttackedTag;
	
	if(!ABS) return;
	ABS->OnAbilityEnded.Remove(AbilityEndedHandle);

	BaseAIController->StateTreeAIComponent->SendStateTreeEvent(Event);
	FinishTask();
}