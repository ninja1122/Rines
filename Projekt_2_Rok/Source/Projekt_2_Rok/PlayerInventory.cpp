// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInventory.h"
#include "Projekt_2_RokCharacter.h"
#include "FakeUpGameInstanceBase.h"


// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInventory::AddToInventory(APickupableActor * actor)
{
	FString goldname = "Gold";

	actor->pickupAddedDelegate.Broadcast(actor);

	if (actor->Name != goldname)
	{
		bool isadded = false;

		for (int i = 0; i < inventory.Num(); i++)
		{
			if (actor->Name == inventory[i]->Name)
			{
				inventory[i]->Quantity += actor->Quantity;

				inventory[i]->QuantityFString = FString::FromInt(inventory[i]->Quantity);

				//UE_LOG(LogTemp, Warning, TEXT("inv: %s"), *FString::FromInt(inventory[i]->Quantity));

				isadded = true;

				actor->Destroy();
			}
		}

		if (!isadded)
		{
			actor->QuantityFString = FString::FromInt(actor->Quantity);

			inventory.Add(actor);
		}
	}

	GoldCoins += actor->GoldVal;

	Cast<UFakeUpGameInstanceBase>(GetWorld()->GetGameInstance())->addedToInventoryDelegate.Broadcast(inventory);
}

void UPlayerInventory::ClearInventory()
{
	inventory.Empty();
	OnUpdateInventory.Broadcast(inventory);
}

void UPlayerInventory::RemoveFromInventory(APickupableActor * actor)
{
	int32 index;
	int32 tak = 0;

	actor->pickupRemovedDelegate.Broadcast(actor);

	for (int i = 0; i < inventory.Num(); i++)
	{
		if (actor->Name == inventory[i]->Name)
		{
			index = i;
		}
	}

	if (inventory.Num() > tak)
	{
		inventory.RemoveAt(index);
		actor->Destroy();
	}

	this->UpdateInventory();
}

void UPlayerInventory::RemoveFromInventoryNoDelete(APickupableActor * actor)
{
	int32 index;
	int32 tak = 0;

	for (int i = 0; i < inventory.Num(); i++)
	{
		if (actor->Name == inventory[i]->Name)
		{
			index = i;
		}
	}

	if (inventory.Num() > tak)
	{
		inventory.RemoveAt(index);
	}

	this->UpdateInventory();
}

void UPlayerInventory::UpdateInventory()
{
	OnUpdateInventory.Broadcast(inventory);
}

void UPlayerInventory::AddGold(int32 GoldValue)
{
	GoldCoins += GoldValue;
}

bool UPlayerInventory::CheckIsInInventory(FString ActorName, int32 Quantity)
{
	for (int32 i = 0; i < inventory.Num(); i++)
	{
		if (inventory[i]->Name == ActorName)
		{
			if (inventory[i]->Quantity >= Quantity)
			{
				return true;
			}
		}
	}

	return false;
}

bool UPlayerInventory::RemoveFromInventoryString(FString ActorName, int32 Quantity)
{
	for (int32 i = 0; i < inventory.Num(); i++)
	{
		if (inventory[i]->Name == ActorName)
		{
			if (Quantity == 0)
			{
				RemoveFromInventory(inventory[i]);

				return true;
			}

			if (Quantity > 0)
			{
				if (Quantity > inventory[i]->Quantity)
				{
					return false;
				}

				if (Quantity == inventory[i]->Quantity)
				{
					RemoveFromInventory(inventory[i]);

					return true;
				}

				if (Quantity < inventory[i]->Quantity)
				{
					inventory[i]->Quantity = inventory[i]->Quantity - Quantity;

					return true;
				}
			}
		}
	}

	return false;
}
