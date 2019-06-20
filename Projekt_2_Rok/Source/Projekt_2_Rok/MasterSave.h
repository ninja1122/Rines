// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MasterSave.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API UMasterSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UMasterSave();
	
	UPROPERTY(EditAnywhere)
	TArray<FString> SaveMasterName;
};
