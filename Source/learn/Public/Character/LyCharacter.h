// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyCharacterBase.h"
#include "LyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API ALyCharacter : public ALyCharacterBase
{
	GENERATED_BODY()
public:
	ALyCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	void InitAbilityActorInfo();

};
