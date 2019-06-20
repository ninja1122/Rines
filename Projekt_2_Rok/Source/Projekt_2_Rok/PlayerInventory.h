// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickupableActor.h"
#include "PlayerInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<APickupableActor*>&, InventoryItems);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_2_ROK_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddToInventory(APickupableActor* actor);

	UFUNCTION(BlueprintCallable)
	void ClearInventory();

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(APickupableActor* actor);

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventoryNoDelete(APickupableActor* actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APickupableActor*> inventory;

	UFUNCTION(BlueprintCallable)
	void UpdateInventory();

	UPROPERTY(BlueprintAssignable, Category = "Pickup")
	FUpdateInventoryDelegate OnUpdateInventory;

	UFUNCTION(BlueprintCallable)
	void AddGold(int32 GoldValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	int32 GoldCoins;

	UFUNCTION(BlueprintCallable)
	bool CheckIsInInventory(FString ActorName, int32 Quantity);

	UFUNCTION(BlueprintCallable)
	bool RemoveFromInventoryString(FString ActorName, int32 Quantity);
};
