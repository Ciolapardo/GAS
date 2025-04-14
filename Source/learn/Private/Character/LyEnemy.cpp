// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyEnemy.h"
#include "learn/learn.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AbilitySystem/LyAttributeSet.h"
#include "UI/Widget/LyUserWidget.h"
#include "Components/WidgetComponent.h"

ALyEnemy::ALyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<ULyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<ULyAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
	
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
	
	if (ULyUserWidget* LyUserWidget = Cast<ULyUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		LyUserWidget->SetWidgetController(this);
	}

	if (const ULyAttributeSet* LyAS = Cast<ULyAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(LyAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(LyAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		OnHealthChanged.Broadcast(LyAS->GetHealth());
		OnMaxHealthChanged.Broadcast(LyAS->GetMaxHealth());
	}

	InitAbilityActorInfo();
}

void ALyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<ULyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitializeDefaultAttributes();
}
