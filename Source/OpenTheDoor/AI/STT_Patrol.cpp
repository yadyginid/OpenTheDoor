// Fill out your copyright notice in the Description page of Project Settings.


#include "STT_Patrol.h"
#include "BaseAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "OpenTheDoor/Characters/AICharacter.h"

void USTT_Patrol::ExecuteTask()
{
	if(!GetWorld() || !AICharacter || !BaseAIController || AICharacter->PatrolPoints.Num() == 0) return;
	const int32 CurrentPatrolIndex = AICharacter->CurrentPatrolIndex;
	
	FAIMoveRequest Req;
	Req.SetGoalActor(AICharacter->PatrolPoints[CurrentPatrolIndex]);
	Req.SetAcceptanceRadius(AcceptanceRadius);
	Req.SetUsePathfinding(true);
	Req.SetAllowPartialPath(true);
	Req.SetCanStrafe(false);

	FNavPathSharedPtr OutPath;

	if (UPathFollowingComponent* PathFollowingComponent = BaseAIController->GetPathFollowingComponent())
	{
		if(MoveFinishedHandle.IsValid()) PathFollowingComponent->OnRequestFinished.Remove(MoveFinishedHandle);
		MoveFinishedHandle = PathFollowingComponent->OnRequestFinished.AddLambda([this](FAIRequestID RequestID, const FPathFollowingResult& Result)
		{
			MoveFinished(RequestID, Result);
		});
	}

	const FPathFollowingRequestResult PathFollowingRequestResult = BaseAIController->MoveTo(Req, &OutPath);
	ActiveRequestId = PathFollowingRequestResult.MoveId;
}

void USTT_Patrol::MoveFinished(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (RequestID != ActiveRequestId || !Result.IsSuccess()) return;
	AICharacter->CurrentPatrolIndex = (AICharacter->CurrentPatrolIndex + 1) % AICharacter->PatrolPoints.Num();
	
	FinishTask();
}
