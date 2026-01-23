// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_Base.generated.h"

class AAICharacter;
class ABaseAIController;
class AAIController;

UCLASS()
class OPENTHEDOOR_API USTT_Base : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Context")
	ABaseAIController* BaseAIController;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Context")
	AAICharacter* AICharacter;
	
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

protected:
	virtual void ExecuteTask();
};
