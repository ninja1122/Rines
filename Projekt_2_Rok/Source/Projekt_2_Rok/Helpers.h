// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/Actor.h"
#include "Helpers.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKT_2_ROK_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static FVector findProjectileTargetPosition(UObject* WorldContextObject, const FVector& start, float distance, const FVector& traceBegin, const FVector& traceDirection, ETraceTypeQuery traceChannel);

	UFUNCTION(BlueprintCallable)
	static FText convertToRomanNumeral(int32 number);
};
