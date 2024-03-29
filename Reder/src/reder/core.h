#pragma once
#ifdef RE_PLATFORM_WINDOWS
	#if RE_DYNAMIC_LINK
		#ifdef RE_DLL_BUILD
			#define DLL_API __declspec(dllexport)
		#else
			#define DLL_API __declspec(dllimport)
		#endif
	#else
		#define DLL_API
	#endif
#else
	#error reder only supports windows! located in core.h
#endif


#define BIT(x) (1 << x)
#define SHOW_TEST_INFO 0
#define SHOW_ALL_DEBUG_INFO 0
#define RE_BUFFER_INT uint32_t

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
 
#define RE_BIND_EVENT(fn) std::bind(&fn,this,std::placeholders::_1)