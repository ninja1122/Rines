// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableActor.h"
#include "SkrzyniaParametry.generated.h"

UCLASS()
class PROJEKT_2_ROK_API ASkrzyniaParametry : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkrzyniaParametry();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		bool isTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		bool Otwieranie;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		bool PrawidlowaKombinacja;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		bool CzekajNaKolejnyZnak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		bool CzySkrzyniaOtworzona;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		TArray<int32> Sekwencja;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ParametySkrzyni)
		TArray<int32> SekwencjaGracza;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Content")
		TArray<APickupableActor*> content;

	
	//VisibleAnywhere
	//EditAnywhere
	
};
