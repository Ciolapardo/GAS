// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/LyWidgetController.h"

void ULyWidgetController::SetWidgetControllerParams(const FwidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void ULyWidgetController::BroadcastInitialValues()
{

}

void ULyWidgetController::BindCallBacksToDependencies()
{

}
