// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LyPlayerController.h"
#include "Interaction/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/LyAbilitySystemComponent.h"
#include "Input/LyInputConfig.h"
#include "LyGameplayTags.h"
#include "Components/SplineComponent.h"
#include "Input/LyInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

ALyPlayerController::ALyPlayerController()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ALyPlayerController::PlayerTick(float DelaTime)
{
	Super::PlayerTick(DelaTime);
	//鼠标命中高亮
	CursorTrace();

	AutoRun();

}

ULyAbilitySystemComponent* ALyPlayerController::GetASC()
{
	if (LyAbilitySystemComponent == nullptr)
	{
		LyAbilitySystemComponent = Cast<ULyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return LyAbilitySystemComponent;
}

void ALyPlayerController::ToggleMouseControl()
{
	bMouseVisible = !bMouseVisible;

	// 显示或隐藏鼠标光标
	bShowMouseCursor = bMouseVisible;
	SetShowMouseCursor(bMouseVisible);

	// 设置输入模式
	if (bMouseVisible)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);

		// 禁用相机旋转
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
		SetIgnoreLookInput(true); // 禁止鼠标控制视角
	}
	else
	{
		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);

		SetIgnoreLookInput(false); // 恢复视角控制
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;

		// 让鼠标回到中心
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		FVector2D Center = ViewportSize * 0.5f;
		SetMouseLocation(Center.X, Center.Y);
	}
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

	//bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);	
	SetInputMode(InputModeData);	

}

void ALyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ULyInputComponent* LyInputComponent = CastChecked<ULyInputComponent>(InputComponent);
	LyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALyPlayerController::Move);
	LyInputComponent->BindAction(SAction, ETriggerEvent::Started, this, &ALyPlayerController::SPress);
	LyInputComponent->BindAction(SAction, ETriggerEvent::Completed, this, &ALyPlayerController::SReleased);
	LyInputComponent->BindAction(ToggleMouseAction, ETriggerEvent::Triggered, this, &ALyPlayerController::ToggleMouseControl);
	LyInputComponent->BindAbilityActions(InputConfig, this, &ALyPlayerController::AbilityInputTagPressed, &ALyPlayerController::AbilityInputTagReleased, &ALyPlayerController::AbilityInputTagHeld);
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

void ALyPlayerController::SPress()
{
	bIsSKeyDown = true;
}

void ALyPlayerController::SReleased()
{
	bIsSKeyDown = false;
}

void ALyPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());	

	if (LastActor != ThisActor)
	{
		if (ThisActor) ThisActor->HighlightActor();
		if (LastActor) LastActor->UnHighlightActor();
	}

}

void ALyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1,3.f, FColor::Red, TEXT("Pressed: ") + InputTag.ToString());
	if (bMouseVisible&&InputTag.MatchesTagExact(FLyGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRuning = false;
	}
	
}

void ALyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FLyGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}

	if (bMouseVisible)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}

		if (!bTargeting&&!bIsSKeyDown)
		{
			APawn* ControlledPawn = GetPawn();
			if (FollowTime <= ShortPressThreshold)
			{
				if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
				{
					Spline->ClearSplinePoints();
					for (const auto& PointLoc : NavPath->PathPoints)
					{
						Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
						DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5);
					}
					if (NavPath->PathPoints.Num() > 2)
					{
						CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					}
					bAutoRuning = true;
				}
			}
			FollowTime = 0.f;
			bTargeting = false;
		}
	} 
}

void ALyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{

	if (!InputTag.MatchesTagExact(FLyGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if(bMouseVisible)
	{
		if (bTargeting || bIsSKeyDown)
		{
			if (GetASC()) 	GetASC()->AbilityInputTagHeld(InputTag);
		}
		else
		{
			FollowTime += GetWorld()->GetDeltaSeconds();

			if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

			if (APawn* ControlledPawn = GetPawn())
			{
				const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(WorldDirection);
			}

		}
	}

	
}

void ALyPlayerController::AutoRun()
{
	if (!bAutoRuning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Size();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRuning = false;
		}
	}
}
