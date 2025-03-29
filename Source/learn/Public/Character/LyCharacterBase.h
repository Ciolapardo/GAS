

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LyCharacterBase.generated.h"

UCLASS()
class LEARN_API ALyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ALyCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
private:


};
