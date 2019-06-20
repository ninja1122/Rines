// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Save_Game.h"
#include "MasterSave.h"
#include "Kismet/GameplayStatics.h"
#include "Projekt_2_RokCharacter.h"
#include "PlayerInventory.h"
#include "NPC_Character.h"
#include "Container.h"
#include "SkrzyniaParametry.h"
#include "Dialogue_NPC.h"
#include "StatystykiPostaci.h"
#include "SaveGamePlayerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveGameDelegate, FString, SaveName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadGameDelegate, FString, SaveName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAmbientDelegate, FString, SaveName);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_2_ROK_API USaveGamePlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USaveGamePlayerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SaveGame(FString SaveName);

	UFUNCTION(BlueprintCallable)
	void LoadGame(FString SaveName);
	
	UFUNCTION(BlueprintCallable)
	static TArray<FString> GetAllSaveGameSlotNames();

	UFUNCTION(BlueprintCallable)
	void MakeMasterSave();

	UFUNCTION(BlueprintCallable)
	void SaveLocation(FString SaveName);

	UFUNCTION(BlueprintCallable)
	void LoadLocation(FString SaveName);

	UFUNCTION(BlueprintCallable)
	void SavePlayer(FString SaveName);

	UFUNCTION(BlueprintCallable)
	void LoadPlayer(FString SaveName);

	UPROPERTY(EditAnywhere, Category = Save)
	TArray<UClass*> EnemiesActorClasses;

	UPROPERTY(EditAnywhere, Category = Save)
	TSubclassOf<UUserWidget> WidgetLoadScreen;

	UPROPERTY()
	UUserWidget* WidgetLoadScreenInstance;

	UPROPERTY(EditAnywhere, Category = Save)
	TSubclassOf<UUserWidget> WidgetSaving;

	UPROPERTY()
	UUserWidget* WidgetSavingInstance;

	UPROPERTY(BlueprintAssignable, Category = "Save")
	FSaveGameDelegate OnSaveGameDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Save")
	FLoadGameDelegate OnLoadGameDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Ambient")
	FAmbientDelegate OnAmbientDelegate;
};
