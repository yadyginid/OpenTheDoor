// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "BaseAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class OPENTHEDOOR_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();

	UFUNCTION(BlueprintCallable, Category="AI")
	AActor* GetCurrentTarget() const { return CurrentTarget; }

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, Category="AI")
	TObjectPtr<UAIPerceptionComponent> PerceptionComp;

	UPROPERTY()
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

private:
	UPROPERTY()
	AActor* CurrentTarget;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
