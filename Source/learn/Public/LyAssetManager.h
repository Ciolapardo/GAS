// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LEARN_API ULyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static ULyAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
	
};
