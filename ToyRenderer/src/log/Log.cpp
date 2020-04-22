#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"


#include <iostream>
#include <fstream>
#include <cstdio>

namespace ToyRenderer{
   
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Initialize()
    {
	
		// Clear exisiting log file. that section is temp for now
		std::remove("logs/Engine_Log.txt");
		std::remove("logs/Client_Log.txt");

		// Engine Logger
		std::vector<spdlog::sink_ptr> Engine_sinks;
		Engine_sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		Engine_sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>( "logs/Engine_Log.txt", 1048576 * 5, 3));
		Engine_sinks[0]->set_pattern("%^[%T] %n: %v%$");
		s_EngineLogger = std::make_shared<spdlog::logger>("Engine_Log", begin(Engine_sinks), end(Engine_sinks));
		s_EngineLogger->set_level(spdlog::level::trace);
		s_EngineLogger->flush_on(spdlog::level::err);
		spdlog::register_logger(s_EngineLogger);

		ENGINE_LOG_INFO("Inialized Engine Log");

		// Client Logger
		std::vector<spdlog::sink_ptr> Client_sinks;
		Client_sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		Client_sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/Client_Log.txt", 1048576 * 5, 3));
		Client_sinks[0]->set_pattern("%^[%T] %n: %v%$");
		s_ClientLogger = std::make_shared<spdlog::logger>("Client_Log", begin(Client_sinks), end(Client_sinks));
		s_ClientLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_ClientLogger);

		CLIENT_LOG_INFO("Inialized Client Log");

    
    }
}
