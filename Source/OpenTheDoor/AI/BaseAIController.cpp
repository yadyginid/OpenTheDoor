// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

ABaseAIController::ABaseAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
	SetPerceptionComponent(*PerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1500.f;
	SightConfig->PeripheralVisionAngleDegrees = 70.f;
	SightConfig->SetMaxAge(1.5f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
	}
}

void ABaseAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!Actor) return;
	if (Stimulus.WasSuccessfullySensed())
	{
		CurrentTarget = Actor;
	}
	else
	{
		if (CurrentTarget == Actor)
		{
			CurrentTarget = nullptr;
		}
	}
}
