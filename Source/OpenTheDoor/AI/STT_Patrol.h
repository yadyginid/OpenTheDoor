// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "STT_Base.h"
#include "STT_Patrol.generated.h"


struct FPathFollowingResult;

UCLASS()
class OPENTHEDOOR_API USTT_Patrol : public USTT_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Input")
	float AcceptanceRadius = 5.f;
	
protected:
	virtual void ExecuteTask() override;

private:
	FAIRequestID ActiveRequestId;
	FDelegateHandle MoveFinishedHandle;
	bool bMoveInProgress = false;

	
	void MoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result);
};
