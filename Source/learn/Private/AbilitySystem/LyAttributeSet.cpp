// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LyAttributeSet.h"
#include "Net/UnrealNetwork.h"

ULyAttributeSet::ULyAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void ULyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ULyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ULyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void ULyAttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth) const
{
	//从服务器同步到客户端所需要的
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULyAttributeSet, Health, OldHealth);	
}

void ULyAttributeSet::OnRep_MaxHealth(FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULyAttributeSet, MaxHealth, OldMaxHealth);
}

void ULyAttributeSet::OnRep_Mana(FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULyAttributeSet, Mana, OldMana);
}

void ULyAttributeSet::OnRep_MaxMana(FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ULyAttributeSet, MaxMana, OldMaxMana);
}
