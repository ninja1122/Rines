#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Core/Public/Serialization/MemoryWriter.h"
#include "Core/Public/Serialization/MemoryReader.h"
#include "CoreUObject/Public/Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SaveGameArchive.generated.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(LogMyGame, Log, All);

struct SaveGameArchiveImpl : public FObjectAndNameAsStringProxyArchive {
	SaveGameArchiveImpl(FArchive& InInnerArchive);

	bool ShouldSkipProperty(const UProperty* InProperty) const;
};

UCLASS(BlueprintType)
class PROJEKT_2_ROK_API USaveGameArchive : public UObject {
	GENERATED_BODY()

	SaveGameArchiveImpl* readArchive;
	SaveGameArchiveImpl* writeArchive;
	FMemoryWriter* memoryWriter;
	FMemoryReader* memoryReader;
	TArray<uint8> data;

	SaveGameArchiveImpl* archive;

public:
	USaveGameArchive();
	~USaveGameArchive();

	UFUNCTION(BlueprintCallable)
	void write(UObject* object);

	UFUNCTION(BlueprintCallable)
	void read(UObject* object);

	UFUNCTION(BlueprintCallable)
	void serialize(UObject* object);

	UFUNCTION(BlueprintCallable)
	void serializeBool(UPARAM(ref) bool& object);

	UFUNCTION(BlueprintCallable)
	void serializeInt(UPARAM(ref) int32& object);

	UFUNCTION(BlueprintCallable)
	void serializeFloat(UPARAM(ref) float& object);

	UFUNCTION(BlueprintCallable)
	void serializeStruct(UStruct* s);

	UFUNCTION(BlueprintCallable)
	TArray<uint8> getData();

	UFUNCTION(BlueprintCallable)
	void setData(const TArray<uint8>& data);
};
