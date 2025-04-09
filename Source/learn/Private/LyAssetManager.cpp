// Fill out your copyright notice in the Description page of Project Settings.


#include "LyAssetManager.h"
#include "LyGameplayTags.h"
#include "AbilitySystemGlobals.h"

ULyAssetManager& ULyAssetManager::Get()
{
	// TODO: 在此处插入 return 语句
	check(GEngine);
	ULyAssetManager* LyAssetManager = Cast<ULyAssetManager>(GEngine->AssetManager);
	return *LyAssetManager;
}

void ULyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FLyGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();

}
