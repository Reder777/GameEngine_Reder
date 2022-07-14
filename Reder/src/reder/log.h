#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


/*
this file encapsulates some spdlog log function 
and creates two logger
corelogger for engine use
clientlogger for app use
more information please visit spdlog in github
ref:https://github.com/gabime/spdlog

*/

namespace reder {


	class DLL_API log
	{
	public:
		static void init();
		//get corelogger 
		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() {
			return coreLogger;
		}
		//get clientlogger
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() {
			return clientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;

	};

}
//core logger macros
#define RE_CORE_INFO(...)  ::reder::log::getCoreLogger()->info(__VA_ARGS__)
#define RE_CORE_ERROR(...) ::reder::log::getCoreLogger()->error(__VA_ARGS__)
#define RE_CORE_DEBUG(...) ::reder::log::getCoreLogger()->debug(__VA_ARGS__)
#define RE_CORE_WARN(...)  ::reder::log::getCoreLogger()->warn(__VA_ARGS__)
#define RE_CORE_FATAL(...) ::reder::log::getCoreLogger()->fatal(__VA_ARGS__)
#define RE_CORE_TRACE(...) ::reder::log::getCoreLogger()->trace(__VA_ARGS__)


//client logger macros
#define RE_CLIENT_INFO(...)  ::reder::log::getClientLogger()->info(__VA_ARGS__)
#define RE_CLIENT_ERROR(...) ::reder::log::getClientLogger()->error(__VA_ARGS__)
#define RE_CLIENT_DEBUG(...) ::reder::log::getClientLogger()->debug(__VA_ARGS__)
#define RE_CLIENT_WARN(...)  ::reder::log::getClientLogger()->warn(__VA_ARGS__)
#define RE_CLIENT_FATAL(...) ::reder::log::getClientLogger()->fatal(__VA_ARGS__)
#define RE_CLIENT_TRACE(...) ::reder::log::getClientLogger()->trace(__VA_ARGS__)