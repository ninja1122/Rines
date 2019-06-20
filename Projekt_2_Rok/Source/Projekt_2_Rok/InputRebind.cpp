#include "InputRebind.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"

bool UInputRebind::InputRebindAction(FInput Action, FInput Original)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings)
	{
		return false;
	}
		
	TArray<FInputActionKeyMapping>& Actions = Settings->ActionMappings;

	bool bFound = false;
	for (FInputActionKeyMapping& Each : Actions)
	{
		if (Each.ActionName.ToString() == Action.ActionName && Each.Key == Original.Key)
		{
			UInputRebind::UpdateActionMapping(Each, Action);
			bFound = true;
			break;
		}
	}

	if (bFound)
	{
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return bFound;
}

bool UInputRebind::InputRebindAxis(FInputAxis Axis, FInputAxis Original)
{
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	if (!Settings) return false;

	TArray<FInputAxisKeyMapping>& Axi = Settings->AxisMappings;

	bool bFound = false;
	for (FInputAxisKeyMapping& Each : Axi)
	{
		if (Each.AxisName.ToString() == Axis.AxisName && Each.Key == Original.Key) 
		{
			UInputRebind::UpdateAxisMapping(Each, Axis);
			bFound = true;
			break;
		}
	}

	if (bFound)
	{
		const_cast<UInputSettings*>(Settings)->SaveKeyMappings();

		for (TObjectIterator<UPlayerInput> It; It; ++It)
		{
			It->ForceRebuildingKeyMaps(true);
		}
	}
	return bFound;
}
