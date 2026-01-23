// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class OPENTHEDOOR_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> PatrolPoints;
	
	int32 CurrentPatrolIndex = 0;
};
