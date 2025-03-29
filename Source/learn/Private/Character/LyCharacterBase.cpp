


#include "Character/LyCharacterBase.h"

ALyCharacterBase::ALyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponHandSocket")); 
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

