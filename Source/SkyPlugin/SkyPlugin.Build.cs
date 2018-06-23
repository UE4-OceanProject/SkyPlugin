// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

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
        //Our PrivatePCH that we want to globally #include
        PrivatePCHHeaderFile = "Private/PrivatePCH.h";

        // Make sure UBT reminds us of how to keep the project IWYU compliant
        bEnforceIWYU = true;

        //Enable IWYU but keep our PrivatePCH in use
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
               // ... add public include paths required here ...
			}
            );


        PrivateIncludePaths.AddRange(
            new string[] {
                "SkyPlugin/Private",
				
				// ... add other private include paths required here ...
			}
            );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
				
				// ... add other public dependencies that you statically link with here ...
			}
            );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "TimePlugin"

				// ... add private dependencies that you statically link with here ...	
			}
            );


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
				// ... add any modules that your module loads dynamically here ...
			}
            );
    }
}

