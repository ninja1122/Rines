// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save_Game.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API USave_Game : public USaveGame
{
	GENERATED_BODY()
	
public:
	USave_Game();

	UPROPERTY(EditAnywhere)
	FTransform SavePlayerTransform;

	UPROPERTY(EditAnywhere)
	int32 SavePlayerGold;

	UPROPERTY(EditAnywhere)
	TArray<FString> SaveInventoryItemsNames;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveInventoryItemsQuantity;

	UPROPERTY(EditAnywhere)
	TArray<FString> SaveWorldActorNames;

	UPROPERTY(EditAnywhere)
	TArray<FString> SaveWorldActorClassNames;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldActorVisibility;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> SaveWorldActorTransform;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveWorldActorQuantity;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveWorldActorGold;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveMissionProgress;

	UPROPERTY(EditAnywhere)
	FString SaveLevelName;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> SaveWorldNPCTransform;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveWorldNPCConversationId;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> SaveWorldNPCDTransform;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldNPCStep;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldNPCAntoni;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldNPCRolnika;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldNPCZielarka;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveWorldNPCMysliwy;


	UPROPERTY(EditAnywhere)
	TArray<bool> SaveCzyJestPytajnik;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerId;

	UPROPERTY(EditAnywhere)
	TArray<FString> SaveContainerItemsNames;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerItemsQuantity;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerItemsGold;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerLockedId;

	UPROPERTY(EditAnywhere)
	TArray<FString> SaveContainerLockedItemsNames;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerLockedItemsQuantity;

	UPROPERTY(EditAnywhere)
	TArray<int32> SaveContainerLockedItemsGold;

	UPROPERTY(EditAnywhere)
	TArray<bool> SaveContainerLockedIsOpen;

	UPROPERTY(EditAnywhere)
	TArray<FTransform> SaveWorldEnemiesTransform;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> SaveWorldEnemiesClasses;

	UPROPERTY(EditAnywhere)
	bool Lvl1introCinematic;

	UPROPERTY(EditAnywhere)
	bool Lvl1GameName;

	UPROPERTY(EditAnywhere)
	bool Lvl1MaciejDrzewoCinematic;

	UPROPERTY(EditAnywhere)
	int SavePlayerlevelPostaci;

	UPROPERTY(EditAnywhere)
	int SavePlayerdoswiadczenie;

	UPROPERTY(EditAnywhere)
	int SavePlayerdoswiadczenieNaKoloejnyPoziom;

	UPROPERTY(EditAnywhere)
	int SavePlayerzdrowie;

	UPROPERTY(EditAnywhere)
	int SavePlayermaxZdrowie;

	UPROPERTY(EditAnywhere)
	int SavePlayerpunktyRozwoju;

	UPROPERTY(EditAnywhere)
	int SavePlayerpoziomKulaOgnia;

	UPROPERTY(EditAnywhere)
	int SavePlayerpoziomKolce;

	UPROPERTY(EditAnywhere)
	int SavePlayerpoziomFalaWody;

	UPROPERTY(EditAnywhere)
	bool SaveAmbientForest;

	UPROPERTY(EditAnywhere)
	bool SaveAmbientWater;
};
