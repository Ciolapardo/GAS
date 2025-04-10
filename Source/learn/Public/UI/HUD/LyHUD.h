// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LyHUD.generated.h"

class ULyUserWidget;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FwidgetControllerParams;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS()
class LEARN_API ALyHUD : public AHUD
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	TObjectPtr<ULyUserWidget> OverlayWidget;

	UFUNCTION()
	UOverlayWidgetController* GetOverlayWidgetController(const FwidgetControllerParams& WCParmas);

	UFUNCTION()
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FwidgetControllerParams& WCParmas);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ABS, UAttributeSet* AS);
protected:


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<ULyUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;	

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
