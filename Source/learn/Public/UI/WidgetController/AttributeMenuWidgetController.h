// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/LyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"


class UAttributeInfo;
struct FLyAttributeInfo;
struct  FGameplayAttribute;
struct FGameplayTag;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FLyAttributeInfo& ,Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class LEARN_API UAttributeMenuWidgetController : public ULyWidgetController
{
	GENERATED_BODY()
public:

	virtual void BindCallBacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

	//UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	//FOnPlayerStatChangedSignature AttributePointsChangedDelegate;

	UFUNCTION(BlueprintCallable)
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

private:

	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
