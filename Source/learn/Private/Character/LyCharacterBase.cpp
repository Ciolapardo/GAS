


#include "Character/LyCharacterBase.h"

ALyCharacterBase::ALyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

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

