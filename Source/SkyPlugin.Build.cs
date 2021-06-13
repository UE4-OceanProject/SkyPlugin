// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

using UnrealBuildTool;

public class SkyPlugin : ModuleRules
{
    public SkyPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(new string[] { });

        PrivateIncludePaths.AddRange(new string[] { });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "TimePlugin"
		});

        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            "Engine"
		});

        DynamicallyLoadedModuleNames.AddRange(new string[] { });
    }
}

