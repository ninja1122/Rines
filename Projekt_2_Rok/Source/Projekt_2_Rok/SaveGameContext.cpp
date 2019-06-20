#include "SaveGameContext.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"

USaveGameContext* USaveGameContext::getSaveGameContext(UObject* WorldContextObject) {
	/*
	auto* playerPawn = WorldContextObject->GetWorld()->GetFirstPlayerController()->GetPawn();

	TArray<uint8> ObjectData;
	if(playerPawn == nullptr)
		return nullptr;

	FMemoryWriter MemoryWriter(ObjectData, true);
	// use a wrapper archive that converts FNames and UObject*'s to strings that can be read back in
	SaveGameArchive MyArchive(MemoryWriter);
	// serialize the object

	int32 v = 123;
	MyArchive << v << v << v;

	playerPawn->Serialize(MyArchive);

	ObjectData.Num();*/

	return nullptr;
}
