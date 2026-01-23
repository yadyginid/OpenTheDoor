// Fill out your copyright notice in the Description page of Project Settings.


#include "GSTT_Manager.h"
#include "BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"

EStateTreeRunStatus UGSTT_Manager::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	AimEventTag = FGameplayTag::RequestGameplayTag(TEXT("State.Aim"));
	NoAimingEventTag = FGameplayTag::RequestGameplayTag(TEXT("State.NoAiming"));
	
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
		Event.Tag = AimEventTag;
		SendEvent(Event);
		return;
	}

	if(!Stimulus.WasSuccessfullySensed() && TargetActor == Actor)
	{
		TargetActor = nullptr;
		Event.Tag = NoAimingEventTag;
		SendEvent(Event);
		return;
	}
}
