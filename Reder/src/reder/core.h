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


#define BIT(x) (1 << x)


#ifdef RE_ENABLE_ASSERT
	#define RE_CORE_ASSERT(x,...)   if(!(x))\
									RE_CORE_ERROR("assertion failed: {0}", __VA_ARGS__); \
									__debugbreak();
	#define RE_CLIENT_ASSERT(x,...) if(!(x))\
									RE_CLIENT_ERROR("assertion failed: {0}", __VA_ARGS__); \
									__debugbreak();
#else
	#define RE_CORE_ASSERT(x,...)
	#define RE_CLIENT_ASSERT(x,...)
#endif
 
