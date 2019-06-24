// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DziennikZadan.h"
#include "PickupableActor.h"
#include "FakeUpGameInstanceBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddedToInventoryDelegate, const TArray<APickupableActor*>&, InventoryItems);

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API UFakeUpGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFakeUpGameInstanceBase();

	virtual void Init();

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FAddedToInventoryDelegate addedToInventoryDelegate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = InputDevice)
	bool bUsingGamepad;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Quests)
	TArray<FMisje> testMisje;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Temp)
	FString LoadSaveName = "N";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 AudioLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 AudioAmbientLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 AudioDialogueLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 GraphicalIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 PostProcessingIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 AAIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 ShadowIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 FPSIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 MBIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 WindowModeIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Settings)
	int32 ResolutionIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Cinematic)
	bool Lvl1introCinematic = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Cinematic)
	bool Lvl1GameName = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Cinematic)
	bool Lvl1MaciejDrzewoCinematic = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
	bool AmbientForest;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
	bool AmbientWater;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Audio)
	bool AmbientOcean;

	UFUNCTION(BlueprintCallable)
	void Reset();
};
