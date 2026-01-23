// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STT_Base.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "STT_Idle.generated.h"

UCLASS()
class OPENTHEDOOR_API USTT_Idle : public USTT_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Input")
	float Duration = 2.f;
	
protected:
	virtual void ExecuteTask() override;

	FTimerHandle IdleTimerHandle;

	UFUNCTION()
	void OnFinishIdle();
};
