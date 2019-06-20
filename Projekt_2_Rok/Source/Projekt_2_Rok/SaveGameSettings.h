// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "SaveSettings.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGameSettings.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API USaveGameSettings : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintCallable)
	static void SaveSettings();

	UFUNCTION(BlueprintCallable)
	static void LoadSettings();
	
};
