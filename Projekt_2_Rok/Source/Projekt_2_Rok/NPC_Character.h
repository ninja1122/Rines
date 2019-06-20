// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC_Character.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class NPC_Role : uint8
{
	Farmer		UMETA(DisplayName = "Rolnik"),
	Rustic 		UMETA(DisplayName = "Wiesniak"),
	Watchman	UMETA(DisplayName = "Straznik"),
	Companion	UMETA(DisplayName = "Towarzysz")
};


UCLASS()
class PROJEKT_2_ROK_API ANPC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
		NPC_Role npc_Role;

	//UPROPERTY()
	TMap<NPC_Role, TArray<FString>> Wypowiedzi_NPC;

};
