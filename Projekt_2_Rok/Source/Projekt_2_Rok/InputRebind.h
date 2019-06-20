#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "InputRebind.generated.h"

USTRUCT(BlueprintType)
struct FInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	FString ActionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	uint32 bShift : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	uint32 bCtrl : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	uint32 bAlt : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputRebind")
	uint32 bCmd : 1;

	FInput() {}
	FInput(const FString InActionName, const FKey InKey, const bool bInShift, const bool bInCtrl, const bool bInAlt, const bool bInCmd)
		: Key(InKey)
		, bShift(bInShift)
		, bCtrl(bInCtrl)
		, bAlt(bInAlt)
		, bCmd(bInCmd)
	{
		ActionName = InActionName;
	}

	FInput(const FInputActionKeyMapping& Action)
		: Key(Action.Key)
		, bShift(Action.bShift)
		, bCtrl(Action.bCtrl)
		, bAlt(Action.bAlt)
		, bCmd(Action.bCmd)
	{
		ActionName = Action.ActionName.ToString();
	}
};

USTRUCT(BlueprintType)
struct FInputAxis
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
	FString AxisName = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
	FKey Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Song")
	float Scale = 1;

	FInputAxis() {}
	FInputAxis(const FString InAxisName, FKey InKey, float InScale)
		: AxisName(InAxisName)
		, Key(InKey)
		, Scale(InScale)
	{ }

	FInputAxis(const FInputAxisKeyMapping& Axis)
		:  Key(Axis.Key)
		, Scale(Axis.Scale)
	{
		AxisName = Axis.AxisName.ToString();
	}
};

UCLASS()
class PROJEKT_2_ROK_API UInputRebind : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "InputRebind")
	static bool InputRebindAction(FInput Action, FInput Original);

	UFUNCTION(BlueprintCallable, Category = "InputRebind")
	static bool InputRebindAxis(FInputAxis Axis, FInputAxis Original);
	
	static FORCEINLINE void UpdateActionMapping(FInputActionKeyMapping& Destination, const FInput& InputBind)
	{
		Destination.Key = InputBind.Key;
		Destination.bShift = InputBind.bShift;
		Destination.bCtrl = InputBind.bCtrl;
		Destination.bAlt = InputBind.bAlt;
		Destination.bCmd = InputBind.bCmd;
	}

	static FORCEINLINE void UpdateAxisMapping(FInputAxisKeyMapping& Destination, const FInputAxis& InputBind)
	{
		Destination.Key = InputBind.Key;
		Destination.Scale = InputBind.Scale;
	}
};
