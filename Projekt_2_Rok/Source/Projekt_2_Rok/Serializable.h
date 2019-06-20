#pragma once

#include "Kismet/KismetSystemLibrary.h"
#include "Serializable.generated.h"

class USaveGameArchive;

UINTERFACE(BlueprintType)
class PROJEKT_2_ROK_API USerializable : public UInterface {
	GENERATED_UINTERFACE_BODY()
};

class PROJEKT_2_ROK_API ISerializable {
	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void serialize(USaveGameArchive* archive);
};
