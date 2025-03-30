// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

ALyPlayerState::ALyPlayerState()
{
	//������ÿ����ͻ��˷���100�θ���	
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));


}

UAbilitySystemComponent* ALyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
