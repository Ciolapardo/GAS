// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyCharacterBase.h"
#include "Interaction/CombatInterface.h"
#include "LyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API ALyCharacter : public ALyCharacterBase, public ICombatInterface
{
	GENERATED_BODY()
public:
	ALyCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual int32 GetPlayerLevel_Implementation() override;

private:
	virtual void InitAbilityActorInfo() override;

};
