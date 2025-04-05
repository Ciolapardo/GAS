// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/LyWidgetController.h"
#include "Delegates/DelegateCombinations.h"
#include "AbilitySystemComponent.h"
#include "OverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealtChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealtChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);
/**
 * 
 */

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{

	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class ULyUserWidget> MessageWidget;
};

UCLASS(BlueprintType,Blueprintable)
class LEARN_API UOverlayWidgetController : public ULyWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallBacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealtChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealtChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	protected: 
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
		TObjectPtr<UDataTable> MessageWidgetDataTable;

		void HealthChanged(const FOnAttributeChangeData& Data) const;
		void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
		void ManaChanged(const FOnAttributeChangeData& Data) const;
		void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
