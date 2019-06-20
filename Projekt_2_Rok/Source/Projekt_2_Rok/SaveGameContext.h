#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CoreUObject/Public/Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "SaveGameContext.generated.h"

UCLASS()
class PROJEKT_2_ROK_API USaveGameContext : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static USaveGameContext* getSaveGameContext(UObject* WorldContextObject);
};
