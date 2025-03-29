// Fill out your copyright notice in the Description page of Project Settings.


#include "LyCharacterBase.h"

// Sets default values
ALyCharacterBase::ALyCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALyCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

