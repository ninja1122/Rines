// Fill out your copyright notice in the Description page of Project Settings.

#include "Helpers.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

FVector UHelpers::findProjectileTargetPosition(UObject* WorldContextObject, const FVector& start, float distance, const FVector& traceBegin, const FVector& traceDirection, ETraceTypeQuery traceChannel) {
	FHitResult hit;
	//if(WorldContextObject->GetWorld()->LineTraceSingleByChannel(hit, traceBegin + traceDirection * 100.f, traceBegin + traceDirection * distance, (ECollisionChannel)traceChannel))
	if(UKismetSystemLibrary::LineTraceSingle(WorldContextObject, traceBegin + traceDirection * 10.f, traceBegin + traceDirection * distance, traceChannel, false, {}, EDrawDebugTrace::None, hit, true))
		return hit.Location;

	FVector result = traceBegin;
	for(int32 i = 0; i < 5000; i++) {
		if(FVector::DotProduct(traceDirection, result - start) > 0 && FVector::Dist(start, result) > distance)
			break;

		result += traceDirection * 1.f;
	}

	return result;
}

FText UHelpers::convertToRomanNumeral(int32 number) {
	struct romandata_t { int32 value; char const* numeral; };
	const struct romandata_t romandata[] = {
		{1000, "M"}, {900, "CM"},
		{500, "D"}, {400, "CD"},
		{100, "C"}, { 90, "XC"},
		{ 50, "L"}, { 40, "XL"},
		{ 10, "X"}, { 9, "IX"},
		{ 5, "V"}, { 4, "IV"},
		{ 1, "I"},
		{ 0, NULL} // end marker
	};

	FString result;
	for(const romandata_t* current = romandata; current->value > 0; ++current) {
		while(number >= current->value) {
			result += current->numeral;
			number -= current->value;
		}
	}

	return FText::FromString(result);
}
