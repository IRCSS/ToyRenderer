#pragma once
#include "Core.h"
#include <string>

#ifdef TOYRENDERER_PLATFORM_WINDOWS
#define TOYRENDERER_EXEPATH(x)	\
                    {char Filename[MAX_PATH]; \
                    GetModuleFileNameA(NULL, Filename, sizeof(Filename));\
                    std::string current_working_dir(Filename);\
                    x = current_working_dir.substr(0, current_working_dir.find_last_of("\\/"));}
#else
#define EXEPATH(x) EXEPATHENGINE_LOG_INFO("No implmentation for get executable full path on this platform.")
#endif // TOYRENDERER_PLATFORM_WINDOWS


#ifdef TOYRENDERER_PLATFORM_WINDOWS
#define TOYRENDERER_STYLE_PATH(x) std::replace(x.begin(), x.end(), '/', '\\')
#endif
namespace ToyRenderer {

	static class TOYRENDERER_API File {

	public: 

		
	};

}