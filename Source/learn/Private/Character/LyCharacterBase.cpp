


#include "Character/LyCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Components/CapsuleComponent.h"
#include "learn/learn.h"

ALyCharacterBase::ALyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile,ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponHandSocket")); 
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ALyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ALyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALyCharacterBase::InitAbilityActorInfo()
{

}

FVector ALyCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void ALyCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(IsValid(GameplayEffectClass));
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	UE_LOG(LogTemp, Log, TEXT("EffectContext created for %s"), *GetName());
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, level, ContextHandle);
	if (!SpecHandle.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create GameplayEffectSpec"));
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("GameplayEffectSpec created with level %f"), level);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
	UE_LOG(LogTemp, Log, TEXT("GameplayEffect successfully applied to target %s"), *GetName());
}

void ALyCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributeEffect,1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributeEffect,1.f);
	ApplyEffectToSelf(DefaultVitalAttributeEffect, 1.f);
}

void ALyCharacterBase::AddCharacterAbilities()
{
	
	if (!HasAuthority()) return;

	ULyAbilitySystemComponent* LyAbilitySystemComponent = CastChecked<ULyAbilitySystemComponent>(AbilitySystemComponent);
	LyAbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

