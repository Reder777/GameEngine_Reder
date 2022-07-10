#pragma once
#ifdef RE_PLATFORM_WINDOWS
	#ifdef RE_DLL_BUILD
		#define DLL_API __declspec(dllexport)
	#else
		#define DLL_API __declspec(dllimport)
	#endif 
#else
	#error reder only supports windows! located in core.h
#endif

