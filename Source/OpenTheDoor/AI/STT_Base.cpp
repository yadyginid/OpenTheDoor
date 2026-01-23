// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_Base.h"

EStateTreeRunStatus USTT_Base::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition)
{
	ExecuteTask();
	return Super::EnterState(Context, Transition);
}

void USTT_Base::ExecuteTask()
{
}
