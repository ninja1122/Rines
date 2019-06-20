// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableActor.h"
#include "Trader.generated.h"

UCLASS()
class PROJEKT_2_ROK_API ATrader : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrader();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	TArray<APickupableActor*> content;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
	int32 GoldQuantity;
	
};
