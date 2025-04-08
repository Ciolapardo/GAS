// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyEnemy.h"
#include "learn/learn.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "AttributeSet.h"


ALyEnemy::ALyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<ULyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>(TEXT("AttributeSet"));

	
	
}

void ALyEnemy::HighlightActor()
{

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ALyEnemy::UnHighlightActor()
{

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ALyEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}

void ALyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

void ALyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<ULyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
