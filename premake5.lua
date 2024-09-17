workspace "TrexEngine"
	architecture "x64"
	configurations {"Debug", "Release"}
	startproject "SandBox"

	OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-----------------------------------------------------------------TrexEngine--------------------------------------------
	project "TrexEngine"
		location "TrexEngine"

		kind "SharedLib"
		language "C++"

		targetdir ("./bin/" .. OutputDir .. "/TrexEngine")
		objdir ("./bin-in/" .. OutputDir .. "/TrexEngine")

		files {
			"./TrexEngine/Source/**.h",
			"./TrexEngine/Source/**.cpp"
		}

		includedirs {
			"./TrexEngine/Source/Trex/Include",
			"/TrexEngine/Source/Trex/Include/GL",
			"/TrexEngine/Source/Trex/Include/GLFW"
		}

		libdirs {
			"./bin/External"
		}

		links {"opengl32", "glew32s", "glfw3", "kernel32", "user32" , "gdi32", "winspool", "comdlg32", "advapi32", "shell32","ole32", 
		"oleaut32", "uuid", "odbc32", "odbccp32"}

		filter ("system:windows")
			defines {"PLATFORM_WINDOWS", "TX_BUILD_DLL", "GLEW_STATIC", "WINDLL"}
			staticruntime "On"
			cppdialect "C++17"
			systemversion "10.0.17763.0"
		
			
		filter ("configurations:Debug")
			symbols "On"
			defines {"DEBUG"}
		filter ("configurations:Release")
			defines {"RELEASE"}
			optimize "On"
			
		filter {"configurations:Debug", "system:windows"}
			buildoptions {"/MDd"}
			
-- --------------------------------------------------GLFW-------------------------------------------------------
-- project "glfw3"
-- location "glfw3"
-- kind "StaticLib"
-- language "C"

-- targetdir ("./bin/" .. OutputDir .. "/glfw3")
-- objdir ("./bin-in/" .. OutputDir .. "/glfw3")

-- files {
-- 	"./glfw/include/**.h",
-- 	"./glfw/src/**.c"
-- }

-- filter ("system:windows")
-- 	defines {"_WIN32", "_GLFW_WIN32"}
-- 	systemversion "10.0.17763.0"
-- 	staticruntime "On"

-- filter("configurations:Debug")
-- 	symbols "On"
-- filter("configurations:Release")
-- 	optimize "On"


-------------------------------------------------SandBox----------------------------------------------

	project "SandBox"
		location "SandBox"
			
		kind "ConsoleApp"
		language "C++"
			
		targetdir ("./bin/" .. OutputDir .. "/SandBox")
		objdir ("./bin-in/" .. OutputDir .. "/SandBox")
			
		files {
			"./SandBox/Source/**.h",
			"./SandBox/Source/**.cpp"
		}
			
		includedirs {
			"./TrexEngine/Source/",
			"./TrexEngine/Source/Trex/Include"
		}
			
		libdirs {
			("./bin/" .. OutputDir)
		}
			
		links {
			"TrexEngine"
		}
			
		filter ("system:windows")
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"
		defines {"PLATFORM_WINDOWS"}
		postbuildcommands {"{COPY} ../bin/" .. OutputDir .. "/TrexEngine/TrexEngine.dll ../bin/" .. OutputDir .. "/SandBox",
						   "{COPY} ../bin/External/vcruntime140_1d.dll ../bin/" .. OutputDir .. "/SandBox"}
			
		filter ("configurations:Debug")
			symbols "On"
			defines {"DEBUG"}

		filter ("configurations:Release")
			optimize "On"
			defines {"RELEASE"}

