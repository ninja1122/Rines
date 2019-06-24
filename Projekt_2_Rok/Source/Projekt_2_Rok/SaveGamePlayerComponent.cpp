// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGamePlayerComponent.h"
#include "FakeUpGameInstanceBase.h"
#include "PlatformFeatures.h"
#include "GameFramework/SaveGame.h"


// Sets default values for this component's properties
USaveGamePlayerComponent::USaveGamePlayerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USaveGamePlayerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	WidgetLoadScreenInstance = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), WidgetLoadScreen);

	WidgetSavingInstance = CreateWidget<UUserWidget>(UGameplayStatics::GetGameInstance(GetWorld()), WidgetSaving);
}


// Called every frame
void USaveGamePlayerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USaveGamePlayerComponent::SaveGame(FString SaveName)
{
	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UPlayerInventory* PlayerInventoryInstance = Cast<UPlayerInventory>(Player->GetComponentByClass(UPlayerInventory::StaticClass()));
	UStatystykiPostaci* PlayerStatistic = Cast<UStatystykiPostaci>(Player->GetComponentByClass(UStatystykiPostaci::StaticClass()));
	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));

	WidgetSavingInstance->AddToViewport();

	//zapis do savegameinstance
	SaveGameInstance->SavePlayerTransform = Player->GetActorTransform();

	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	SaveGameInstance->SaveLevelName = LevelName;

	OnSaveGameDelegate.Broadcast(SaveName);

	for (int i = 0; i < PlayerInventoryInstance->inventory.Num(); i++)
	{
		SaveGameInstance->SaveInventoryItemsNames.Add(PlayerInventoryInstance->inventory[i]->Name);
		SaveGameInstance->SaveInventoryItemsQuantity.Add(PlayerInventoryInstance->inventory[i]->Quantity);
	}

	SaveGameInstance->SavePlayerGold = PlayerInventoryInstance->GoldCoins;

	SaveGameInstance->SavePlayerlevelPostaci = PlayerStatistic->levelPostaci;
	SaveGameInstance->SavePlayerdoswiadczenie = PlayerStatistic->doswiadczenie;
	SaveGameInstance->SavePlayerdoswiadczenieNaKoloejnyPoziom = PlayerStatistic->doswiadczenieNaKoloejnyPoziom;
	SaveGameInstance->SavePlayerpunktyRozwoju = PlayerStatistic->punktyRozwoju;

	SaveGameInstance->SaveAmbientForest = GameInstance->AmbientForest;
	SaveGameInstance->SaveAmbientWater = GameInstance->AmbientWater;
	SaveGameInstance->SaveAmbientOcean = GameInstance->AmbientOcean;

	for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

		SaveGameInstance->SaveWorldActorNames.Add(APickupActor->GetName());
		SaveGameInstance->SaveWorldActorVisibility.Add(APickupActor->GetIsHidden());
		SaveGameInstance->SaveWorldActorTransform.Add(APickupActor->GetActorTransform());
		SaveGameInstance->SaveWorldActorQuantity.Add(APickupActor->Quantity);
		SaveGameInstance->SaveWorldActorGold.Add(APickupActor->GoldVal);
		SaveGameInstance->SaveWorldActorClassNames.Add(APickupActor->Name);
	}

/*	for (TActorIterator<ANPC_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ANPC_Character* ANPC = Cast<ANPC_Character>(*ActorItr);

		SaveGameInstance->SaveWorldNPCTransform.Add(ANPC->GetTransform());
	}*/

	for (TActorIterator<ADialogue_NPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ADialogue_NPC* ANPC = Cast<ADialogue_NPC>(*ActorItr);

		SaveGameInstance->SaveWorldNPCConversationId.Add(ANPC->IDconversation);
		SaveGameInstance->SaveWorldNPCDTransform.Add(ANPC->GetActorTransform());
		SaveGameInstance->SaveWorldNPCAntoni.Add(ANPC->CzyZadanieAntoniWykonane);
		SaveGameInstance->SaveWorldNPCRolnika.Add(ANPC->CzyZadanieRolnikWykonane);
		SaveGameInstance->SaveWorldNPCZielarka.Add(ANPC->CzyZadanieZielarkaWykonane);
		SaveGameInstance->SaveWorldNPCMysliwy.Add(ANPC->CzyZadanieMysliwyWykonane);
		SaveGameInstance->SaveWorldNPCStep.Add(ANPC->CzyRozpoczacOdInnejLini);
		SaveGameInstance->SaveCzyJestPytajnik.Add(ANPC->CzyJestPytajnik);
	}		

	SaveGameInstance->SaveMissionProgress.Empty();
	for (int32 i = 0; i < GameInstance->testMisje.Num(); i++)
	{
		SaveGameInstance->SaveMissionProgress.Add(GameInstance->testMisje[i].KtoraCzescMisji);
		SaveGameInstance->Lvl1introCinematic = GameInstance->Lvl1introCinematic;
		SaveGameInstance->Lvl1GameName = GameInstance->Lvl1GameName;
		SaveGameInstance->Lvl1MaciejDrzewoCinematic = GameInstance->Lvl1MaciejDrzewoCinematic;
	}

	int32 counter = 0;
	for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AContainer* Container = Cast<AContainer>(*ActorItr);

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			SaveGameInstance->SaveContainerId.Add(counter);
			SaveGameInstance->SaveContainerItemsNames.Add(Container->content[i]->Name);
			SaveGameInstance->SaveContainerItemsQuantity.Add(Container->content[i]->Quantity);
			SaveGameInstance->SaveContainerItemsGold.Add(Container->content[i]->GoldVal);
		}

		counter++;
	}

	counter = 0;
	for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			SaveGameInstance->SaveContainerLockedId.Add(counter);
			SaveGameInstance->SaveContainerLockedItemsNames.Add(Container->content[i]->Name);
			SaveGameInstance->SaveContainerLockedItemsQuantity.Add(Container->content[i]->Quantity);
			SaveGameInstance->SaveContainerLockedItemsGold.Add(Container->content[i]->GoldVal);
			SaveGameInstance->SaveContainerLockedIsOpen.Add(Container->CzySkrzyniaOtworzona);
		}

		counter++;
	}

	for (int32 i = 0; i < EnemiesActorClasses.Num(); i++)
	{	
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemiesActorClasses[i], FoundActors);

		for (int32 j = 0; j < FoundActors.Num(); j++)
		{
			SaveGameInstance->SaveWorldEnemiesTransform.Add(FoundActors[j]->GetTransform());
			SaveGameInstance->SaveWorldEnemiesClasses.Add(EnemiesActorClasses[i]);
		}
	}

	if (SaveName == "QuickSave")
	{
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);
	}
	else
	{
		UMasterSave* SaveGameInstanceMaster = Cast<UMasterSave>(UGameplayStatics::CreateSaveGameObject(UMasterSave::StaticClass()));

		FString SaveNameMaster = "MasterSave";

		SaveGameInstanceMaster = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(SaveNameMaster, 0));

		for (int32 i = 0; i < SaveGameInstanceMaster->SaveMasterName.Num(); i++)
		{
			if (SaveName == SaveGameInstanceMaster->SaveMasterName[i])
			{
				SaveGameInstanceMaster->SaveMasterName.RemoveAt(i);
			}
		}

		SaveGameInstanceMaster->SaveMasterName.Insert(SaveName,0);
		
		UGameplayStatics::SaveGameToSlot(SaveGameInstanceMaster, SaveNameMaster, 0);
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);
	}

	WidgetSavingInstance->RemoveFromParent();
}

void USaveGamePlayerComponent::LoadGame(FString SaveName)
{
//	UE_LOG(LogTemp, Warning, TEXT("load: %s"), *FString::FromInt(SaveGameInstance->SaveInventoryItemsQuantity[i]));

	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UPlayerInventory* PlayerInventoryInstance = Cast<UPlayerInventory>(Player->GetComponentByClass(UPlayerInventory::StaticClass()));
	UFakeUpGameInstanceBase* GameInstance = Cast<UFakeUpGameInstanceBase>(UGameplayStatics::GetGameInstance(GetWorld()));
	UStatystykiPostaci* PlayerStatistic = Cast<UStatystykiPostaci>(Player->GetComponentByClass(UStatystykiPostaci::StaticClass()));
	
	WidgetLoadScreenInstance->AddToViewport();
	SaveGameInstance = Cast<USave_Game>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));

	FString LevelName = GetWorld()->GetMapName();
	LevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (LevelName != SaveGameInstance->SaveLevelName)
	{
		GameInstance->LoadSaveName = SaveName;
		UGameplayStatics::OpenLevel(GetWorld(), FName(*SaveGameInstance->SaveLevelName));		
	}

	OnLoadGameDelegate.Broadcast(SaveName);

	Player->SetActorTransform(SaveGameInstance->SavePlayerTransform);

	PlayerInventoryInstance->GoldCoins = SaveGameInstance->SavePlayerGold;

	PlayerStatistic->levelPostaci = SaveGameInstance->SavePlayerlevelPostaci;
	PlayerStatistic->doswiadczenie = SaveGameInstance->SavePlayerdoswiadczenie;
	PlayerStatistic->doswiadczenieNaKoloejnyPoziom = SaveGameInstance->SavePlayerdoswiadczenieNaKoloejnyPoziom;
	SaveGameInstance->SavePlayerpunktyRozwoju = PlayerStatistic->punktyRozwoju;

	GameInstance->AmbientForest = SaveGameInstance->SaveAmbientForest;
	GameInstance->AmbientWater = SaveGameInstance->SaveAmbientWater;
	GameInstance->AmbientOcean = SaveGameInstance->SaveAmbientOcean;
	OnAmbientDelegate.Broadcast(SaveName);

	PlayerInventoryInstance->ClearInventory();

	for (int32 i = 0; i < SaveGameInstance->SaveMissionProgress.Num(); i++)
	{
		GameInstance->testMisje[i].KtoraCzescMisji = SaveGameInstance->SaveMissionProgress[i];
		GameInstance->Lvl1introCinematic = SaveGameInstance->Lvl1introCinematic;
		GameInstance->Lvl1GameName = SaveGameInstance->Lvl1GameName;
		GameInstance->Lvl1MaciejDrzewoCinematic = SaveGameInstance->Lvl1MaciejDrzewoCinematic;
	}

	int count = 0;

/*	if (SaveGameInstance->SaveWorldNPCTransform.Num() > 0)
	{
		for (TActorIterator<ANPC_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ANPC_Character* ANPC = Cast<ANPC_Character>(*ActorItr);

			ANPC->SetActorTransform(SaveGameInstance->SaveWorldNPCTransform[count]);
			count++;
		}
	}*/
	
	if (SaveGameInstance->SaveWorldNPCConversationId.Num() > 0)
	{
		count = 0;
		for (TActorIterator<ADialogue_NPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ADialogue_NPC* ANPC = Cast<ADialogue_NPC>(*ActorItr);
			ANPC->IDconversation = SaveGameInstance->SaveWorldNPCConversationId[count];
			ANPC->SetActorTransform(SaveGameInstance->SaveWorldNPCDTransform[count]);
			ANPC->CzyZadanieAntoniWykonane = SaveGameInstance->SaveWorldNPCAntoni[count];
			ANPC->CzyZadanieRolnikWykonane = SaveGameInstance->SaveWorldNPCRolnika[count];
			ANPC->CzyZadanieZielarkaWykonane = SaveGameInstance->SaveWorldNPCZielarka[count];
			ANPC->CzyZadanieMysliwyWykonane = SaveGameInstance->SaveWorldNPCMysliwy[count];
			ANPC->CzyRozpoczacOdInnejLini = SaveGameInstance->SaveWorldNPCStep[count];
			ANPC->CzyJestPytajnik = SaveGameInstance->SaveCzyJestPytajnik[count];

			count++;
		}
	}

	//load world objects
	if (SaveGameInstance->SaveWorldActorNames.Num() > 0)
	{
		for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

			bool bischanged = false;

			for (int32 i = 0; i < SaveGameInstance->SaveWorldActorNames.Num(); i++)
			{
				if (APickupActor->GetName() == SaveGameInstance->SaveWorldActorNames[i])
				{
					if (SaveGameInstance->SaveWorldActorTransform[i].Equals(APickupActor->GetTransform(), 0.000001f))
					{
						APickupActor->SetHidden(SaveGameInstance->SaveWorldActorVisibility[i]);
						APickupActor->Quantity = SaveGameInstance->SaveWorldActorQuantity[i];
						APickupActor->GoldVal = SaveGameInstance->SaveWorldActorGold[i];

						bischanged = true;
					}
				}
			}

			if (!bischanged)
			{
				APickupActor->Destroy();
			}
		}

		for (int32 i = 0; i < SaveGameInstance->SaveWorldActorNames.Num(); i++)
		{
			bool bexist = false;

			for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

				if (SaveGameInstance->SaveWorldActorNames[i] == APickupActor->GetName())
				{
					bexist = true;
				}
			}

			if (!bexist)
			{
				FString actorpath = "Class'/Game/Blueprints/Inventory/";
				actorpath.Append(SaveGameInstance->SaveWorldActorClassNames[i]);
				actorpath.Append(".");
				actorpath.Append(SaveGameInstance->SaveWorldActorClassNames[i]);
				actorpath.Append("_C'");

				FRotator rotator = Player->GetActorRotation();
				FVector spawnLocation = Player->GetActorLocation();

				APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

				if (InventoryItem)
				{
					InventoryItem->GoldVal = SaveGameInstance->SaveWorldActorGold[i];
					InventoryItem->Quantity = SaveGameInstance->SaveWorldActorQuantity[i];

					InventoryItem->SetHidden(SaveGameInstance->SaveWorldActorVisibility[i]);

					InventoryItem->SetActorTransform(SaveGameInstance->SaveWorldActorTransform[i]);
				}	
			}
		}
	}
	

	//load player inventory
	if (SaveGameInstance->SaveInventoryItemsNames.Num() > 0)
	{
		for (int32 i = 0; i < SaveGameInstance->SaveInventoryItemsNames.Num(); i++)
		{
			FString actorpath = "Class'/Game/Blueprints/Inventory/";
			actorpath.Append(SaveGameInstance->SaveInventoryItemsNames[i]);
			actorpath.Append(".");
			actorpath.Append(SaveGameInstance->SaveInventoryItemsNames[i]);
			actorpath.Append("_C'");

			FRotator rotator = Player->GetActorRotation();
			FVector spawnLocation = Player->GetActorLocation();
			spawnLocation.Z = spawnLocation.Z - 500;

			APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveInventoryItemsQuantity[i]);

			InventoryItem->GoldVal = 0;

			InventoryItem->Quantity = SaveGameInstance->SaveInventoryItemsQuantity[i];

			PlayerInventoryInstance->AddToInventory(InventoryItem);

			InventoryItem->SetActorHiddenInGame(true);
		}
	}
	
	if (SaveGameInstance->SaveContainerId.Num() > 0)
	{
		for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AContainer* Container = Cast<AContainer>(*ActorItr);

			for (int32 i = 0; i < Container->content.Num(); i++)
			{
				Container->content[i]->Destroy();
			}
			Container->content.Empty();
		}

		int32 counter = 0;
		for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AContainer* Container = Cast<AContainer>(*ActorItr);

			for (int32 i = 0; i < SaveGameInstance->SaveContainerId.Num(); i++)
			{
				if (SaveGameInstance->SaveContainerId[i] == counter)
				{
					FString actorpath = "Class'/Game/Blueprints/Inventory/";
					actorpath.Append(SaveGameInstance->SaveContainerItemsNames[i]);
					actorpath.Append(".");
					actorpath.Append(SaveGameInstance->SaveContainerItemsNames[i]);
					actorpath.Append("_C'");

					FRotator rotator = Player->GetActorRotation();
					FVector spawnLocation = Player->GetActorLocation();

					APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

					InventoryItem->GoldVal = SaveGameInstance->SaveContainerItemsGold[i];
					InventoryItem->Quantity = SaveGameInstance->SaveContainerItemsQuantity[i];

					InventoryItem->SetHidden(true);

					Container->content.Add(InventoryItem);
				}
			}

			counter++;
		}
	}
	
	if (SaveGameInstance->SaveContainerLockedId.Num() > 0)
	{
		for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

			for (int32 i = 0; i < Container->content.Num(); i++)
			{
				Container->content[i]->Destroy();
			}
			Container->content.Empty();
		}

		int32 counter = 0;
		for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

			for (int32 i = 0; i < SaveGameInstance->SaveContainerLockedId.Num(); i++)
			{
				if (SaveGameInstance->SaveContainerLockedId[i] == counter)
				{
					FString actorpath = "Class'/Game/Blueprints/Inventory/";
					actorpath.Append(SaveGameInstance->SaveContainerLockedItemsNames[i]);
					actorpath.Append(".");
					actorpath.Append(SaveGameInstance->SaveContainerLockedItemsNames[i]);
					actorpath.Append("_C'");

					FRotator rotator = Player->GetActorRotation();
					FVector spawnLocation = Player->GetActorLocation();

					APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

					InventoryItem->GoldVal = SaveGameInstance->SaveContainerLockedItemsGold[i];
					InventoryItem->Quantity = SaveGameInstance->SaveContainerLockedItemsQuantity[i];

					InventoryItem->SetHidden(true);

					Container->content.Add(InventoryItem);

					Container->CzySkrzyniaOtworzona = SaveGameInstance->SaveContainerLockedIsOpen[i];
				}
			}

			counter++;
		}
	}
	
	if (SaveGameInstance->SaveWorldEnemiesClasses.Num() > 0)
	{
		for (int32 i = 0; i < EnemiesActorClasses.Num(); i++)
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemiesActorClasses[i], FoundActors);

			for (int32 j = 0; j < FoundActors.Num(); j++)
			{
				FoundActors[j]->Destroy();
			}
		}

		for (int32 i = 0; i < SaveGameInstance->SaveWorldEnemiesClasses.Num(); i++)
		{
			GetWorld()->SpawnActorAbsolute<AActor>(SaveGameInstance->SaveWorldEnemiesClasses[i].Get(), SaveGameInstance->SaveWorldEnemiesTransform[i], FActorSpawnParameters());
		}
	}	

	WidgetLoadScreenInstance->RemoveFromParent();
}

void USaveGamePlayerComponent::SaveLocation(FString SaveName)
{
	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));

	for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

		SaveGameInstance->SaveWorldActorNames.Add(APickupActor->GetName());
		SaveGameInstance->SaveWorldActorVisibility.Add(APickupActor->GetIsHidden());
		SaveGameInstance->SaveWorldActorTransform.Add(APickupActor->GetActorTransform());
		SaveGameInstance->SaveWorldActorQuantity.Add(APickupActor->Quantity);
		SaveGameInstance->SaveWorldActorGold.Add(APickupActor->GoldVal);
		SaveGameInstance->SaveWorldActorClassNames.Add(APickupActor->Name);
	}

/*	for (TActorIterator<ANPC_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ANPC_Character* ANPC = Cast<ANPC_Character>(*ActorItr);

		SaveGameInstance->SaveWorldNPCTransform.Add(ANPC->GetTransform());
	}*/

	for (TActorIterator<ADialogue_NPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ADialogue_NPC* ANPC = Cast<ADialogue_NPC>(*ActorItr);

		SaveGameInstance->SaveWorldNPCConversationId.Add(ANPC->IDconversation);
		SaveGameInstance->SaveWorldNPCDTransform.Add(ANPC->GetActorTransform());
		SaveGameInstance->SaveWorldNPCAntoni.Add(ANPC->CzyZadanieAntoniWykonane);
		SaveGameInstance->SaveWorldNPCRolnika.Add(ANPC->CzyZadanieRolnikWykonane);
		SaveGameInstance->SaveWorldNPCZielarka.Add(ANPC->CzyZadanieZielarkaWykonane);
		SaveGameInstance->SaveWorldNPCMysliwy.Add(ANPC->CzyZadanieMysliwyWykonane);
		SaveGameInstance->SaveWorldNPCStep.Add(ANPC->CzyRozpoczacOdInnejLini);
		SaveGameInstance->SaveCzyJestPytajnik.Add(ANPC->CzyJestPytajnik);
	}

	int32 counter = 0;
	for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AContainer* Container = Cast<AContainer>(*ActorItr);	

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			SaveGameInstance->SaveContainerId.Add(counter);
			SaveGameInstance->SaveContainerItemsNames.Add(Container->content[i]->Name);
			SaveGameInstance->SaveContainerItemsQuantity.Add(Container->content[i]->Quantity);
			SaveGameInstance->SaveContainerItemsGold.Add(Container->content[i]->GoldVal);
		}

		counter++;
	}

	counter = 0;
	for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			SaveGameInstance->SaveContainerLockedId.Add(counter);
			SaveGameInstance->SaveContainerLockedItemsNames.Add(Container->content[i]->Name);
			SaveGameInstance->SaveContainerLockedItemsQuantity.Add(Container->content[i]->Quantity);
			SaveGameInstance->SaveContainerLockedItemsGold.Add(Container->content[i]->GoldVal);
			SaveGameInstance->SaveContainerLockedIsOpen.Add(Container->CzySkrzyniaOtworzona);
		}

		counter++;
	}

	for (int32 i = 0; i < EnemiesActorClasses.Num(); i++)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemiesActorClasses[i], FoundActors);

		for (int32 j = 0; j < FoundActors.Num(); j++)
		{
			SaveGameInstance->SaveWorldEnemiesTransform.Add(FoundActors[j]->GetTransform());
			SaveGameInstance->SaveWorldEnemiesClasses.Add(EnemiesActorClasses[i]);
		}
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);
}

void USaveGamePlayerComponent::LoadLocation(FString SaveName)
{
	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	SaveGameInstance = Cast<USave_Game>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));

	//load world objects
	for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

		bool bischanged = false;

		for (int32 i = 0; i < SaveGameInstance->SaveWorldActorNames.Num(); i++)
		{
			if (APickupActor->GetName() == SaveGameInstance->SaveWorldActorNames[i])
			{
				if (SaveGameInstance->SaveWorldActorTransform[i].Equals(APickupActor->GetTransform(), 0.000001f))
				{
					APickupActor->SetHidden(SaveGameInstance->SaveWorldActorVisibility[i]);
					APickupActor->Quantity = SaveGameInstance->SaveWorldActorQuantity[i];
					APickupActor->GoldVal = SaveGameInstance->SaveWorldActorGold[i];

					bischanged = true;
				}
			}
		}

		if (!bischanged)
		{
			APickupActor->Destroy();
		}
	}

	for (int32 i = 0; i < SaveGameInstance->SaveWorldActorNames.Num(); i++)
	{
		bool bexist = false;

		for (TActorIterator<APickupableActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			APickupableActor* APickupActor = Cast<APickupableActor>(*ActorItr);

			if (SaveGameInstance->SaveWorldActorNames[i] == APickupActor->GetName())
			{
				bexist = true;
			}
		}

		if (!bexist)
		{
			FString actorpath = "Class'/Game/Blueprints/Inventory/";
			actorpath.Append(SaveGameInstance->SaveWorldActorClassNames[i]);
			actorpath.Append(".");
			actorpath.Append(SaveGameInstance->SaveWorldActorClassNames[i]);
			actorpath.Append("_C'");

			FRotator rotator = Player->GetActorRotation();
			FVector spawnLocation = Player->GetActorLocation();

			APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

			InventoryItem->GoldVal = SaveGameInstance->SaveWorldActorGold[i];
			InventoryItem->Quantity = SaveGameInstance->SaveWorldActorQuantity[i];

			InventoryItem->SetHidden(SaveGameInstance->SaveWorldActorVisibility[i]);

			InventoryItem->SetActorTransform(SaveGameInstance->SaveWorldActorTransform[i]);
		}
	}

	int count = 0;
/*	for (TActorIterator<ANPC_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ANPC_Character* ANPC = Cast<ANPC_Character>(*ActorItr);

		ANPC->SetActorTransform(SaveGameInstance->SaveWorldNPCTransform[count]);
		count++;
	}*/

	count = 0;
	for (TActorIterator<ADialogue_NPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ADialogue_NPC* ANPC = Cast<ADialogue_NPC>(*ActorItr);
		ANPC->IDconversation = SaveGameInstance->SaveWorldNPCConversationId[count];
		ANPC->SetActorTransform(SaveGameInstance->SaveWorldNPCDTransform[count]);
		ANPC->CzyZadanieAntoniWykonane = SaveGameInstance->SaveWorldNPCAntoni[count];
		ANPC->CzyZadanieRolnikWykonane = SaveGameInstance->SaveWorldNPCRolnika[count];
		ANPC->CzyZadanieZielarkaWykonane = SaveGameInstance->SaveWorldNPCZielarka[count];
		ANPC->CzyZadanieMysliwyWykonane = SaveGameInstance->SaveWorldNPCMysliwy[count];
		ANPC->CzyRozpoczacOdInnejLini = SaveGameInstance->SaveWorldNPCStep[count];
		ANPC->CzyJestPytajnik = SaveGameInstance->SaveCzyJestPytajnik[count];

		count++;
	}

	for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AContainer* Container = Cast<AContainer>(*ActorItr);

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			Container->content[i]->Destroy();
		}
		Container->content.Empty();
	}

	int32 counter = 0;
	for (TActorIterator<AContainer> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AContainer* Container = Cast<AContainer>(*ActorItr);

		for (int32 i = 0; i < SaveGameInstance->SaveContainerId.Num(); i++)
		{
			if (SaveGameInstance->SaveContainerId[i] == counter)
			{
				FString actorpath = "Class'/Game/Blueprints/Inventory/";
				actorpath.Append(SaveGameInstance->SaveContainerItemsNames[i]);
				actorpath.Append(".");
				actorpath.Append(SaveGameInstance->SaveContainerItemsNames[i]);
				actorpath.Append("_C'");

				FRotator rotator = Player->GetActorRotation();
				FVector spawnLocation = Player->GetActorLocation();

				APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

				InventoryItem->GoldVal = SaveGameInstance->SaveContainerItemsGold[i];
				InventoryItem->Quantity = SaveGameInstance->SaveContainerItemsQuantity[i];

				InventoryItem->SetHidden(true);

				Container->content.Add(InventoryItem);
			}
		}

		counter++;
	}

	for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

		for (int32 i = 0; i < Container->content.Num(); i++)
		{
			Container->content[i]->Destroy();
		}
		Container->content.Empty();
	}

	counter = 0;
	for (TActorIterator<ASkrzyniaParametry> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ASkrzyniaParametry* Container = Cast<ASkrzyniaParametry>(*ActorItr);

		for (int32 i = 0; i < SaveGameInstance->SaveContainerLockedId.Num(); i++)
		{
			if (SaveGameInstance->SaveContainerLockedId[i] == counter)
			{
				FString actorpath = "Class'/Game/Blueprints/Inventory/";
				actorpath.Append(SaveGameInstance->SaveContainerLockedItemsNames[i]);
				actorpath.Append(".");
				actorpath.Append(SaveGameInstance->SaveContainerLockedItemsNames[i]);
				actorpath.Append("_C'");

				FRotator rotator = Player->GetActorRotation();
				FVector spawnLocation = Player->GetActorLocation();

				APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveWorldActorQuantity[i]);

				InventoryItem->GoldVal = SaveGameInstance->SaveContainerLockedItemsGold[i];
				InventoryItem->Quantity = SaveGameInstance->SaveContainerLockedItemsQuantity[i];

				InventoryItem->SetHidden(true);

				Container->content.Add(InventoryItem);

				Container->CzySkrzyniaOtworzona = SaveGameInstance->SaveContainerLockedIsOpen[i];
			}
		}

		counter++;
	}

	for (int32 i = 0; i < EnemiesActorClasses.Num(); i++)
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemiesActorClasses[i], FoundActors);

		for (int32 j = 0; j < FoundActors.Num(); j++)
		{
			FoundActors[j]->Destroy();
		}
	}

	for (int32 i = 0; i < SaveGameInstance->SaveWorldEnemiesClasses.Num(); i++)
	{
		GetWorld()->SpawnActorAbsolute<AActor>(SaveGameInstance->SaveWorldEnemiesClasses[i].Get(), SaveGameInstance->SaveWorldEnemiesTransform[i], FActorSpawnParameters());
	}
}

void USaveGamePlayerComponent::SavePlayer(FString SaveName)
{
	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UPlayerInventory* PlayerInventoryInstance = Cast<UPlayerInventory>(Player->GetComponentByClass(UPlayerInventory::StaticClass()));
	UStatystykiPostaci* PlayerStatistic = Cast<UStatystykiPostaci>(Player->GetComponentByClass(UStatystykiPostaci::StaticClass()));

	for (int i = 0; i < PlayerInventoryInstance->inventory.Num(); i++)
	{
		SaveGameInstance->SaveInventoryItemsNames.Add(PlayerInventoryInstance->inventory[i]->Name);
		SaveGameInstance->SaveInventoryItemsQuantity.Add(PlayerInventoryInstance->inventory[i]->Quantity);
	}

	OnSaveGameDelegate.Broadcast(SaveName);

	SaveGameInstance->SavePlayerGold = PlayerInventoryInstance->GoldCoins;

	SaveGameInstance->SavePlayerlevelPostaci = PlayerStatistic->levelPostaci;
	SaveGameInstance->SavePlayerdoswiadczenie = PlayerStatistic->doswiadczenie;
	SaveGameInstance->SavePlayerdoswiadczenieNaKoloejnyPoziom = PlayerStatistic->doswiadczenieNaKoloejnyPoziom;
	SaveGameInstance->SavePlayerpunktyRozwoju = PlayerStatistic->punktyRozwoju;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveName, 0);
}

void USaveGamePlayerComponent::LoadPlayer(FString SaveName)
{
	USave_Game* SaveGameInstance = Cast<USave_Game>(UGameplayStatics::CreateSaveGameObject(USave_Game::StaticClass()));
	AProjekt_2_RokCharacter* Player = Cast<AProjekt_2_RokCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	UPlayerInventory* PlayerInventoryInstance = Cast<UPlayerInventory>(Player->GetComponentByClass(UPlayerInventory::StaticClass()));
	UStatystykiPostaci* PlayerStatistic = Cast<UStatystykiPostaci>(Player->GetComponentByClass(UStatystykiPostaci::StaticClass()));

	SaveGameInstance = Cast<USave_Game>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));

	OnLoadGameDelegate.Broadcast(SaveName);

	PlayerInventoryInstance->GoldCoins = SaveGameInstance->SavePlayerGold;

	PlayerStatistic->levelPostaci = SaveGameInstance->SavePlayerlevelPostaci;
	PlayerStatistic->doswiadczenie = SaveGameInstance->SavePlayerdoswiadczenie;
	PlayerStatistic->doswiadczenieNaKoloejnyPoziom = SaveGameInstance->SavePlayerdoswiadczenieNaKoloejnyPoziom;
	SaveGameInstance->SavePlayerpunktyRozwoju = PlayerStatistic->punktyRozwoju;

	PlayerInventoryInstance->ClearInventory();

	//load player inventory
	for (int32 i = 0; i < SaveGameInstance->SaveInventoryItemsNames.Num(); i++)
	{
		FString actorpath = "Class'/Game/Blueprints/Inventory/";
		actorpath.Append(SaveGameInstance->SaveInventoryItemsNames[i]);
		actorpath.Append(".");
		actorpath.Append(SaveGameInstance->SaveInventoryItemsNames[i]);
		actorpath.Append("_C'");

		FRotator rotator = Player->GetActorRotation();
		FVector spawnLocation = Player->GetActorLocation();
		spawnLocation.Z = spawnLocation.Z - 500;

		APickupableActor* InventoryItem = Player->SpawnActor(actorpath, rotator, spawnLocation, SaveGameInstance->SaveInventoryItemsQuantity[i]);

		InventoryItem->GoldVal = 0;

		InventoryItem->Quantity = SaveGameInstance->SaveInventoryItemsQuantity[i];

		PlayerInventoryInstance->AddToInventory(InventoryItem);

		InventoryItem->SetActorHiddenInGame(true);
	}
}

TArray<FString> USaveGamePlayerComponent::GetAllSaveGameSlotNames()
{	
	UMasterSave* SaveGameInstance = Cast<UMasterSave>(UGameplayStatics::CreateSaveGameObject(UMasterSave::StaticClass()));

	FString SaveName = "MasterSave";

	SaveGameInstance = Cast<UMasterSave>(UGameplayStatics::LoadGameFromSlot(SaveName, 0));

	return SaveGameInstance->SaveMasterName;
}

void USaveGamePlayerComponent::MakeMasterSave()
{ 
	UMasterSave* SaveGameInstanceMaster = Cast<UMasterSave>(UGameplayStatics::CreateSaveGameObject(UMasterSave::StaticClass()));

	FString SaveNameMaster = "MasterSave";

	UGameplayStatics::SaveGameToSlot(SaveGameInstanceMaster, SaveNameMaster, 0);
}