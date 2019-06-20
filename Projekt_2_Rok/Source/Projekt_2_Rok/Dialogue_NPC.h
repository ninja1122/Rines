// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dialogue_NPC.generated.h"

UCLASS()
class PROJEKT_2_ROK_API ADialogue_NPC : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogue_NPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		int IDconversation = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		int conversation = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		bool CzyRozpoczacOdInnejLini = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		bool CzyJestPytajnik = false;

	//Soltys
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Soltys)
		bool CzyZadanieAntoniWykonane = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Soltys)
		bool CzyZadanieRolnikWykonane = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Soltys)
		bool CzyZadanieMysliwyWykonane = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Soltys)
		bool CzyZadanieZielarkaWykonane = false;



	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		TArray<int32> tableConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		TArray<int32> tableLineConversation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialogue_NPC_Klas)
		TMap<int32, int32> MapTest;
	*/
};
