// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

	public class SkyPlugin : ModuleRules
	    {
		private string ModulePath
			{
			get { return Path.GetDirectoryName(ModuleDirectory); }
			}

		private string ThirdPartyPath
			{
			get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
			}
	
        public SkyPlugin(ReadOnlyTargetRules Target) : base(Target)
		    {
            PrivateIncludePaths.AddRange(new string[] {	"SkyPlugin/Private" });

			// Make sure UBT reminds us of how to keep the project IWYU compliant
			bEnforceIWYU = true;

			//Enable IWYU but keep our PrivatePCH in use
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			//Our PrivatePCH that we want to globally #include
			PrivatePCHHeaderFile = "Classes/SkyPluginPrivatePCH.h";
        
			PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject", "InputCore", "RHI", "RenderCore" });
		    }
	    }
    