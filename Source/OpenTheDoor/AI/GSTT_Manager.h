// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "Perception/AIPerceptionTypes.h"
#include "GSTT_Manager.generated.h"

class UAIPerceptionComponent;
class AAICharacter;
class ABaseAIController;

UCLASS()
class OPENTHEDOOR_API UGSTT_Manager : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Output")
	AActor* TargetActor;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Context")
	ABaseAIController* BaseAIController;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Context")
	AAICharacter* AICharacter;

	UPROPERTY()
	UAIPerceptionComponent* AIPerceptionComponent;

	FGameplayTag AimEventTag;
	FGameplayTag NoAimingEventTag;
	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
