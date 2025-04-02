// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/LyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	const ULyAttributeSet* LyAttributeSet = CastChecked<ULyAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(LyAttributeSet->GetHealth());
	OnHealthChanged.Broadcast(LyAttributeSet->GetMaxHealth());
	
}
