// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "LyEnemy.generated.h"


class UWidgetComponent;
/**
 * 
 */
UCLASS()
class LEARN_API ALyEnemy : public ALyCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	ALyEnemy();
	/*选中提示接口*/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	virtual int32 GetPlayerLevel_Implementation() override;
				
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

};
