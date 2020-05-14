#pragma once

#include "Core.h"
#include "vendor/spdlog/spdlog.h"
#include <memory>

namespace ToyRenderer {

	class TOYRENDERER_API Log {
	// PUBLIC ======================================================================================
	public: 
		static void Initialize();
		static void ShutDown();
		
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    // ______________________________________________________________________________________________
	// PRIVATE ======================================================================================
    #pragma warning( disable : 4251)  
    // std containers are not dllexported. This could cause issues if their functions are inlined on the client side and cause linking error. Private stuff wont be inlined so I will disable them
	private: 
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

    #pragma warning(default:4251) // Turning the 4251 back on		
	};
	
}


#define ENGINE_LOG_TRACE(...) 	Log::GetEngineLogger()->trace    (__VA_ARGS__)
#define ENGINE_LOG_DEBUG(...)   Log::GetEngineLogger()->debug    (__VA_ARGS__)
#define ENGINE_LOG_INFO(...) 	Log::GetEngineLogger()->info     (__VA_ARGS__)
#define ENGINE_LOG_WARN(...) 	Log::GetEngineLogger()->warn     (__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) 	Log::GetEngineLogger()->error    (__VA_ARGS__)
#define ENGINE_LOG_FATAL(...) 	Log::GetEngineLogger()->critical (__VA_ARGS__)

#define CLIENT_LOG_TRACE(...) 	Log::GetClientLogger()->trace    (__VA_ARGS__)
#define CLIENT_LOG_DEBUG(...)   Log::GetClientLogger()->debug    (__VA_ARGS__)
#define CLIENT_LOG_INFO(...) 	Log::GetClientLogger()->info     (__VA_ARGS__)
#define CLIENT_LOG_WARN(...) 	Log::GetClientLogger()->warn     (__VA_ARGS__)
#define CLIENT_LOG_ERROR(...) 	Log::GetClientLogger()->error    (__VA_ARGS__)
#define CLIENT_LOG_FATAL(...) 	Log::GetClientLogger()->critical (__VA_ARGS__)