workspace "C-proj"
configurations {"Debug", "Release"}
group"__C_proj"

project "Filters"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++14"
    targetdir "Filters/bin/%{cfg.buildcfg}"
    includedirs {"Filters/"}
    buildoptions {"-Wall"}
    files { "Filters/"}
    filter "configurations:Debug"
        -- defines {"ADD_FS_PATH_SUPPORT"}
        -- links{"png"}
        symbols "On"
        filter "configurations:Release"
        optimize "On"
    
project "Tideman_Elections"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++14"
    targetdir "Tideman_Elections/bin/%{cfg.buildcfg}"
    includedirs {"Tideman_Elections/ "}
    buildoptions {"-Wall"}
    files { "Tideman_Elections/"}
    filter "configurations:Debug"
        symbols "On"
        filter "configurations:Release"
        optimize "On"
    
project "Audio_Volume_Modifier"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++14"
    targetdir "Audio_Volume_Modifier/bin/%{cfg.buildcfg}"
    includedirs {"Audio_Volume_Modifier/"}
    buildoptions {"-Wall"}
    files { "Audio_Volume_Modifier/"}
    filter "configurations:Debug"
        symbols "On"
        filter "configurations:Release"
        optimize "On"
    
project "Readability_Test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++14"
    targetdir "Readablity_Test/bin/%{cfg.buildcfg}"
    includedirs {"Readablity_Test/"}
    buildoptions {"-Wall"}
    files { "Readablity_Test/"}
    filter "configurations:Debug"
        symbols "On"
        filter "configurations:Release"
        optimize "On"
    
project "Runoff_elections"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++14"
    targetdir "Runoff_Elections/bin/%{cfg.buildcfg}"
    includedirs {"Runoff_Elections/"}
    buildoptions {"-Wall"}
    files { "Runoff_Elections/"}
    filter "configurations:Debug"
        symbols "On"
        filter "configurations:Release"
        optimize "On"
    
