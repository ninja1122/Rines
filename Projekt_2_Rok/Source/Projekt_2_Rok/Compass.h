// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Compass.generated.h"

UCLASS()
class PROJEKT_2_ROK_API ACompass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACompass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
