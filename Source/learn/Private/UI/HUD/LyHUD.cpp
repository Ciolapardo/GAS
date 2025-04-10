// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LyHUD.h"
#include "UI/Widget/LyUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

UOverlayWidgetController* ALyHUD::GetOverlayWidgetController(const FwidgetControllerParams& WCParmas)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass); 
		OverlayWidgetController->SetWidgetControllerParams(WCParmas);
		OverlayWidgetController->BindCallBacksToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* ALyHUD::GetAttributeMenuWidgetController(const FwidgetControllerParams& WCParmas)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParmas);
		AttributeMenuWidgetController->BindCallBacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

void ALyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ABS, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set in BP_LyHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set in BP_LyHUD"));

	ULyUserWidget* Widget = CreateWidget<ULyUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<ULyUserWidget>(Widget);
	const FwidgetControllerParams widgetControllerParams(PC, PS, ABS, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(widgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();
	Widget->AddToViewport();

}

