// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/LyEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/LyAttributeSet.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "Components/SphereComponent.h"


ALyEffectActor::ALyEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);	

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void ALyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const ULyAttributeSet* LyAttributeSet = Cast<ULyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(ULyAttributeSet::StaticClass()));

		ULyAttributeSet* AttributeSet = const_cast<ULyAttributeSet*>(LyAttributeSet);
		AttributeSet->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ALyEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void ALyEffectActor::BeginPlay()
{
	Super::BeginPlay();
	//¹«Ê½ÉèÖÃ
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ALyEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ALyEffectActor::EndOverlap);
}


