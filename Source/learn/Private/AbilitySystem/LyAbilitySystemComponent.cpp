// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "LyGameplayTags.h"

void ULyAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ULyAbilitySystemComponent::EffectApplied);

}

void ULyAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);

}
