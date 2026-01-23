// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_Idle.h"


void USTT_Idle::ExecuteTask()
{
	if (!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(IdleTimerHandle, this, &ThisClass::OnFinishIdle, Duration, false);
}

void USTT_Idle::OnFinishIdle()
{
	FinishTask();
}
