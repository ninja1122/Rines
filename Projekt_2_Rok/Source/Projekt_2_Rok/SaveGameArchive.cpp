#include "SaveGameArchive.h"
#include "Serializable.h"

//General Log
DEFINE_LOG_CATEGORY(LogMyGame);


SaveGameArchiveImpl::SaveGameArchiveImpl(FArchive& InInnerArchive) :
	FObjectAndNameAsStringProxyArchive(InInnerArchive, false) {
	ArIsSaveGame = true;
}

bool SaveGameArchiveImpl::ShouldSkipProperty(const UProperty* InProperty) const {
	if(ArIsSaveGame == false)
		return false;

	return FObjectAndNameAsStringProxyArchive::ShouldSkipProperty(InProperty);
}

USaveGameArchive::~USaveGameArchive() {
	delete writeArchive;
	delete memoryWriter;
	delete readArchive;
	delete memoryReader;
}

USaveGameArchive::USaveGameArchive() {
	memoryWriter = new FMemoryWriter(data, true);
	memoryReader = new FMemoryReader(data, true);
	writeArchive = new SaveGameArchiveImpl(*memoryWriter);
	readArchive = new SaveGameArchiveImpl(*memoryReader);

	archive = writeArchive;
}

void USaveGameArchive::write(UObject* object) {
	object->Serialize(*writeArchive);
}

void USaveGameArchive::read(UObject* object) {
	object->Serialize(*readArchive);
}

void USaveGameArchive::serialize(UObject* object) {
	object->Serialize(*archive);
	
	// Too good to be true...
	/*UE_LOG(LogMyGame, Display, TEXT("%s"), "Test");

	for(TFieldIterator<UProperty> propertyIt(object->GetClass()); propertyIt; ++propertyIt) {
		bool isStruct = propertyIt->IsA<UStructProperty>();
		if(isStruct && (propertyIt->GetPropertyFlags() & EPropertyFlags::CPF_SaveGame) != 0) {
			auto* s = Cast<UStructProperty>(*propertyIt);
			archive->ArIsSaveGame = false;
			auto* sc = s->Struct;
			for(TFieldIterator<UProperty> propertyIt2(sc); propertyIt2; ++propertyIt2) {	
				propertyIt2->Serialize(*archive);
			}

			archive->ArIsSaveGame = true;
		}
	}*/

	if(object->GetClass()->ImplementsInterface(USerializable::StaticClass())) {
		ISerializable::Execute_serialize(object, this);
	}
}

void USaveGameArchive::serializeBool(bool& object) {
	*archive << object;
}

void USaveGameArchive::serializeInt(int32& object) {
	*archive << object;
}

void USaveGameArchive::serializeFloat(float& object) {
	*archive << object;
}

void USaveGameArchive::serializeStruct(UStruct* s) {

}

TArray<uint8> USaveGameArchive::getData() {
	return data;
}

void USaveGameArchive::setData(const TArray<uint8>& data) {
	this->data = data;
	this->archive = readArchive;
}
