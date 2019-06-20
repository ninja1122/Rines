// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API USaveSettings : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	int32 AudioLevel;

	UPROPERTY(EditAnywhere)
	int32 AudioAmbientLevel;

	UPROPERTY(EditAnywhere)
	int32 AudioDialogueLevel;

	UPROPERTY(EditAnywhere)
	int32 GraphicalIndex;
	
	UPROPERTY(EditAnywhere)
	int32 PostProcessingIndex;

	UPROPERTY(EditAnywhere)
	int32 AAIndex;

	UPROPERTY(EditAnywhere)
	int32 ShadowIndex;

	UPROPERTY(EditAnywhere)
	int32 FPSIndex;

	UPROPERTY(EditAnywhere)
	int32 MBIndex;

	UPROPERTY(EditAnywhere)
	int32 WindowModeIndex;

	UPROPERTY(EditAnywhere)
	int32 ResolutionIndex;
};
