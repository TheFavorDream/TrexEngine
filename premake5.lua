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
			"./TrexEngine/Source/Trex/3rdparty/GL",
			"./TrexEngine/Source/Trex/Renderer/",
			"./TrexEngine/Source/Trex/Window/",
			"./TrexEngine/Source/Trex/Core/",
			"./TrexEngine/Source/Trex/Debug/",
			"./TrexEngine/Source/Trex/Application/",
			"./TrexEngine/Source/Trex/Platform/",
			"./TrexEngine/Source/Trex/3rdparty/glfw/include",
			"./TrexEngine/Source/Trex/3rdparty/ImGui/Include"
		}

		libdirs {
			"./bin/"..OutputDir.."/glfw",
			"./bin/External"
		}

		links {"opengl32", "glew32s", "glfw", "ImGui","kernel32", "user32" , "gdi32", "winspool", "comdlg32", "advapi32", "shell32","ole32", 
		"oleaut32", "uuid", "odbc32", "odbccp32"}

		filter ("system:windows")
			defines {"PLATFORM_WINDOWS", "TX_BUILD_DLL", "GLEW_STATIC", "WINDLL"}
			staticruntime "On"
			cppdialect "C++17"
			systemversion "10.0.17763.0"
		
			
		filter ("configurations:Debug")
			symbols "On"
			defines {"TX_DEBUG"}
		filter ("configurations:Release")
			defines {"TX_RELEASE"}
			optimize "On"
			
		filter {"configurations:Debug", "system:windows"}
			buildoptions {"/MDd"}
		filter {"system:windows", "configurations:Release"}
			buildoptions {"/MD"}
			
-- --------------------------------------------------GLFW-------------------------------------------------------
	project "glfw"
		location "./TrexEngine/Source/Trex/3rdparty/glfw"
		kind "StaticLib"
		language "C"

		targetdir ("./bin/" .. OutputDir .. "/glfw")
		objdir ("./bin-in/" .. OutputDir .. "/glfw")

		files {
			"./TrexEngine/Source/Trex/3rdparty/glfw/include/**.h",
			"./TrexEngine/Source/Trex/3rdparty/glfw/src/**.c"
		}

		filter ("system:windows")
			defines {"_WIN32", "_GLFW_WIN32"}
			systemversion "10.0.17763.0"
			staticruntime "On"

		filter("configurations:Debug")
			symbols "On"
		filter("configurations:Release")
			optimize "On"

		filter {"system:windows", "configurations:Debug"}
			buildoptions {"/MDd"}
		filter {"system:windows", "configurations:Release"}
			buildoptions {"/MT"}


----------------------------------ImGui--------------------------------------------------------

		project "ImGui"
			location "./TrexEngine/Source/Trex/3rdparty/ImGui"
			kind "StaticLib"
			language "C++"
			targetdir ("./bin/" .. OutputDir .. "/ImGui")
			objdir ("./bin-in/" .. OutputDir .. "/ImGui")
	
			includedirs {
				"./TrexEngine/Source/Trex/3rdparty/glfw/include/"
			}

			files {
				"./TrexEngine/Source/Trex/3rdparty/ImGui/Include/**.h",
				"./TrexEngine/Source/Trex/3rdparty/ImGui/Src/**.cpp"
			}
	
			filter ("system:windows")
				systemversion "10.0.17763.0"
				staticruntime "On"
				cppdialect "C++17"
	
			filter("configurations:Debug")
				symbols "On"
			filter("configurations:Release")
				optimize "On"
	
			filter {"system:windows", "configurations:Debug"}
				buildoptions {"/MDd"}
			filter {"system:windows", "configurations:Release"}
				buildoptions {"/MD"}
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
			"./TrexEngine/Source/"
		}
			
		libdirs {
			("./bin/"..OutputDir.."/TrexEngine")
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

		filter {"system:windows", "configurations:Debug"}
			buildoptions {"/MDd"}

		filter {"system:windows", "configurations:Release"}
			buildoptions {"/MD"}
