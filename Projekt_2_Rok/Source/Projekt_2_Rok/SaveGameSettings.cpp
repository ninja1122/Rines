// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameSettings.h"
#include "FakeUpGameInstanceBase.h"
#include "PlatformFeatures.h"
#include "Engine/World.h"
#include "GameFramework/SaveGame.h"

void USaveGameSettings::SaveSettings()
{
	USaveSettings* SaveGameInstance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));

	TArray<APlayerController*> playerList; 
	GEngine->GetAllLocalPlayerControllers(playerList);
//	playerList[0]->GetWorld()->GetGameInstance();

//	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(GEngine->GetWorld()->GetGameInstance());

	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(playerList[0]->GetWorld()->GetGameInstance());

	SaveGameInstance->AudioLevel = GameInstance->AudioLevel;
	SaveGameInstance->AudioAmbientLevel = GameInstance->AudioAmbientLevel;
	SaveGameInstance->AudioDialogueLevel = GameInstance->AudioDialogueLevel;
	SaveGameInstance->GraphicalIndex = GameInstance->GraphicalIndex;
	SaveGameInstance->PostProcessingIndex = GameInstance->PostProcessingIndex;
	SaveGameInstance->AAIndex = GameInstance->AAIndex;
	SaveGameInstance->ShadowIndex = GameInstance->ShadowIndex;
	SaveGameInstance->FPSIndex = GameInstance->FPSIndex;
	SaveGameInstance->MBIndex = GameInstance->MBIndex;
	SaveGameInstance->WindowModeIndex = GameInstance->WindowModeIndex;
	SaveGameInstance->ResolutionIndex = GameInstance->ResolutionIndex;

	FString SaveName = "SaveSettings";
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);	
}


void USaveGameSettings::LoadSettings()
{
	USaveSettings* SaveGameInstance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));

	TArray<APlayerController*> playerList;
	GEngine->GetAllLocalPlayerControllers(playerList);

	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(playerList[0]->GetWorld()->GetGameInstance());

//	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(GEngine->GetWorld()->GetGameInstance());

	//UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));

	FString SaveName = "SaveSettings";
	SaveGameInstance = Cast<USaveSettings>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));

	GameInstance->AudioLevel = SaveGameInstance->AudioLevel;
	GameInstance->AudioAmbientLevel = SaveGameInstance->AudioAmbientLevel;
	GameInstance->AudioDialogueLevel = SaveGameInstance->AudioDialogueLevel;
	GameInstance->GraphicalIndex = SaveGameInstance->GraphicalIndex;
	GameInstance->PostProcessingIndex = SaveGameInstance->PostProcessingIndex;
	GameInstance->AAIndex = SaveGameInstance->AAIndex;
	GameInstance->ShadowIndex = SaveGameInstance->ShadowIndex;
	GameInstance->FPSIndex = SaveGameInstance->FPSIndex;
	GameInstance->MBIndex = SaveGameInstance->MBIndex;
	GameInstance->WindowModeIndex = SaveGameInstance->WindowModeIndex;
	GameInstance->ResolutionIndex = SaveGameInstance->ResolutionIndex;
}

