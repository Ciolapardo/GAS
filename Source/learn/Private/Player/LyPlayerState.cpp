// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyPlayerState.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "AbilitySystem/LyAttributeSet.h"

ALyPlayerState::ALyPlayerState()
{
	//服务器每秒向客户端发送100次更新	
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<ULyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULyAttributeSet>(TEXT("AttributeSet"));


}

UAbilitySystemComponent* ALyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
