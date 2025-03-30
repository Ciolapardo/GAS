// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "LyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API ALyEnemy : public ALyCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	ALyEnemy();
	/*选中提示接口*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;


};
