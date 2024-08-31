#pragma once

#ifdef PLATFORM_WINDOWS

	#ifdef TX_BUILD_DLL
		#define TX_API _declspec(dllexport)	
	#else
		#define TX_API _declspec(dllimport)	
	#endif
#else
	#error Trex Engine Only Supports Windows
#endif