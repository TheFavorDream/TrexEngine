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


#ifdef PLATFORM_WINDOWS
	#include <windows.h>
#endif


typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned int		uint32;
typedef unsigned long int   uint64;

typedef char				int8;
typedef short int			int16;
typedef int					int32;
typedef long int			int64;

typedef float float32;
typedef double float64;