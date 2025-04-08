// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyPlayerState.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "AbilitySystem/LyAttributeSet.h"
#include "Net/UnrealNetwork.h"

ALyPlayerState::ALyPlayerState()
{
	//服务器每秒向客户端发送100次更新	
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<ULyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<ULyAttributeSet>(TEXT("AttributeSet"));


}

void ALyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ALyPlayerState, Level);
	DOREPLIFETIME(ALyPlayerState, XP);
}

UAbilitySystemComponent* ALyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALyPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level, Level > OldLevel);
}

void ALyPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
