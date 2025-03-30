// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"

ALyPlayerController::ALyPlayerController()
{
	bReplicates = true;

}

void ALyPlayerController::PlayerTick(float DelaTime)
{
	Super::PlayerTick(DelaTime);

	CursorTrace();
}

void ALyPlayerController::BeginPlay()
{
	Super::BeginPlay();	
	check(LyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(LyContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);	
	SetInputMode(InputModeData);	

}

void ALyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* LyInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	LyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALyPlayerController::Move);
}

void ALyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControllPawn = GetPawn<APawn>())
	{
		ControllPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControllPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ALyPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());	

	if (LastActor == nullptr) {
		if(ThisActor != nullptr)
			ThisActor->HighlightActor();
	}
	else if (LastActor != ThisActor)
	{
		LastActor->UnHighlightActor();
		if (ThisActor != nullptr)
			ThisActor->HighlightActor();
	}

}
