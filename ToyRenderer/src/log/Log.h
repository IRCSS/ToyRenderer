#pragma once

#include "spdlog/spdlog.h"
#include <memory>
namespace ToyRenderer {

	class Log {
	public: 
		static void Initialize();
		
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private: 
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		
	};
	
}


#define ENGINE_LOG_TRACE(...) 	ToyRenderer::Log::GetEngineLogger()->trace    (__VA_ARGS__)
#define ENGINE_LOG_DEBUG(...)   ToyRenderer::Log::GetEngineLogger()->debug    (__VA_ARGS__)
#define ENGINE_LOG_INFO(...) 	ToyRenderer::Log::GetEngineLogger()->info     (__VA_ARGS__)
#define ENGINE_LOG_WARN(...) 	ToyRenderer::Log::GetEngineLogger()->warn     (__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) 	ToyRenderer::Log::GetEngineLogger()->error    (__VA_ARGS__)
#define ENGINE_LOG_FATAL(...) 	ToyRenderer::Log::GetEngineLogger()->critical (__VA_ARGS__)

#define CLIENT_LOG_TRACE(...) 	ToyRenderer::Log::GetClientLogger()->trace    (__VA_ARGS__)
#define CLIENT_LOG_DEBUG(...)   ToyRenderer::Log::GetClientLogger()->debug    (__VA_ARGS__)
#define CLIENT_LOG_INFO(...) 	ToyRenderer::Log::GetClientLogger()->info     (__VA_ARGS__)
#define CLIENT_LOG_WARN(...) 	ToyRenderer::Log::GetClientLogger()->warn     (__VA_ARGS__)
#define CLIENT_LOG_ERROR(...) 	ToyRenderer::Log::GetClientLogger()->error    (__VA_ARGS__)
#define CLIENT_LOG_FATAL(...) 	ToyRenderer::Log::GetClientLogger()->critical (__VA_ARGS__)