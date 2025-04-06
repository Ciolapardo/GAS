// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/LyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "Player/LyPlayerState.h"
#include "Player/LyPlayerController.h"
#include "UI/HUD/LyHUD.h"
ALyCharacter::ALyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void ALyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//服务器端初始化player
	InitAbilityActorInfo();
}

void ALyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//客户端初始化player
	InitAbilityActorInfo();
}

void ALyCharacter::InitAbilityActorInfo()
{
	ALyPlayerState* LyPlayerState = GetPlayerState<ALyPlayerState>();
	check(LyPlayerState);
	LyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(LyPlayerState, this);

	Cast<ULyAbilitySystemComponent>(LyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = LyPlayerState->GetAbilitySystemComponent();
	AttributeSet = LyPlayerState->GetAttributeSet();

	if (ALyPlayerController* LyPlayerController = Cast<ALyPlayerController>(GetController()))
	{
		if (ALyHUD* LyHUD = Cast<ALyHUD>(LyPlayerController->GetHUD()))
		{
			LyHUD->InitOverlay(LyPlayerController, LyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
