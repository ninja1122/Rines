// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <string>
#include "DziennikZadan.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJEKT_2_ROK_API UDziennikZadan : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDziennikZadan();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};


USTRUCT(BlueprintType)
struct FMisje
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NazwaMisji;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool MainMission;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 KtoraCzescMisji = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NPCid = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> OpisMisji;
};