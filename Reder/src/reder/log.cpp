#include "log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace reder {


	std::shared_ptr<spdlog::logger> log::coreLogger;
	std::shared_ptr<spdlog::logger> log::clientLogger;

	void log::init() {
		spdlog::set_pattern("[%D %T]  [thread %t] %n : %v%$");
		coreLogger = spdlog::stdout_color_mt("Reder");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("Client");
		clientLogger->set_level(spdlog::level::trace);
	}
}
