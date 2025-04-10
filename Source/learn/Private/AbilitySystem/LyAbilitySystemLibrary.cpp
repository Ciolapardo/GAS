// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LyAbilitySystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "LyGameplayTags.h"
#include "Game/LyGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/LyPlayerState.h"
#include "UI/HUD/LyHUD.h"
#include "UI/WidgetController/LyWidgetController.h"

bool ULyAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FwidgetControllerParams& OutWCParams, ALyHUD*& OutAuraHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutAuraHUD = Cast<ALyHUD>(PC->GetHUD());
		if (OutAuraHUD)
		{
			ALyPlayerState* PS = PC->GetPlayerState<ALyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* ULyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FwidgetControllerParams WCParams;
	ALyHUD* LyHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, LyHUD))
	{
		return LyHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UAttributeMenuWidgetController* ULyAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FwidgetControllerParams WCParams;
	ALyHUD* LyHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, LyHUD))
	{
		return LyHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}
