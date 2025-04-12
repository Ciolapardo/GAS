// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "LyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class ULyInputConfig;
class ULyAbilitySystemComponent;
class USplineComponent;
/**
 * 
 */
UCLASS()
class LEARN_API ALyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ALyPlayerController();
	virtual void PlayerTick(float DelaTime) override;

	ULyAbilitySystemComponent* GetASC();

	void ToggleMouseControl();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// «∑Òœ‘ æ Û±Í
	UPROPERTY(VisibleAnywhere)
	bool bMouseVisible = false;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> LyContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
	FHitResult CursorHit;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<ULyInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<ULyAbilitySystemComponent> LyAbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ToggleMouseAction;


	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bTargeting = false;
	bool bAutoRuning = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
