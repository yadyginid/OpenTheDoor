// Fill out your copyright notice in the Description page of Project Settings.


#include "GSTT_Manager.h"
#include "BaseAIController.h"
#include "OpenTheDoor/Characters/PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"

EStateTreeRunStatus UGSTT_Manager::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	AimEventTag = FGameplayTag::RequestGameplayTag("State.Aim");
	NoAimingEventTag = FGameplayTag::RequestGameplayTag("State.NoAiming");
	SafeZoneTag = FGameplayTag::RequestGameplayTag("Effects.Safe");
	
	if(BaseAIController && BaseAIController->GetAIPerceptionComponent())
	{
		AIPerceptionComponent = BaseAIController->GetAIPerceptionComponent();
		AIPerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	}
	FStateTreeEvent Event;
	Event.Tag = NoAimingEventTag;
	SendEvent(Event);
	
	return Super::EnterState(Context, Transition);
}

void UGSTT_Manager::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(!Actor) return;
	FStateTreeEvent Event;
	
	if(Stimulus.WasSuccessfullySensed() && !TargetActor)
	{
		TargetActor = Actor;
		auto Player = Cast<APlayerCharacter>(TargetActor);
		if(!Player) return;
		
		TargetABS = Cast<APlayerCharacter>(TargetActor)->GetAbilitySystemComponent();

		BindOnSafeZone();
		
		bool bHasSafe = TargetABS->HasMatchingGameplayTag(SafeZoneTag);
		bHasSafe ? Event.Tag = NoAimingEventTag : Event.Tag = AimEventTag;
		
		SendEvent(Event);
		return;
	}

	if(!Stimulus.WasSuccessfullySensed() && TargetActor == Actor)
	{
		UnbindSafeZone();
		
		TargetActor = nullptr;
		TargetABS = nullptr;
		
		Event.Tag = NoAimingEventTag;
		SendEvent(Event);
		return;
	}
}

void UGSTT_Manager::OnSafeZoneTagChanged(FGameplayTag GameplayTag, int32 NewCount)
{
	FStateTreeEvent Event;

	NewCount > 0 ? Event.Tag = NoAimingEventTag : Event.Tag = AimEventTag;
	SendEvent(Event);
}

void UGSTT_Manager::BindOnSafeZone()
{
	if(!TargetABS) return;
	SafeZoneHandle = TargetABS->RegisterGameplayTagEvent(SafeZoneTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UGSTT_Manager::OnSafeZoneTagChanged);
}

void UGSTT_Manager::UnbindSafeZone()
{
	if (TargetABS && SafeZoneHandle.IsValid())
	{
		TargetABS->RegisterGameplayTagEvent(SafeZoneTag, EGameplayTagEventType::NewOrRemoved).Remove(SafeZoneHandle);
	}
	SafeZoneHandle.Reset();
}