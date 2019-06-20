// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Projekt_2_RokEditorTarget : TargetRules
{
	public Projekt_2_RokEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Projekt_2_Rok");
	}
}
