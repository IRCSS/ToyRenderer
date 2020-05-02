#include "File.h"
#include "log/Log.h"

namespace ToyRenderer {
	std::string File::GetExecutableFullPath()
	{
       #ifdef TOYRENDERER_PLATFORM_WINDOWS
       
		char Filename[MAX_PATH]; //this is a char buffer
		GetModuleFileNameA(NULL, Filename, sizeof(Filename));
		std::string current_working_dir(Filename);

       		return current_working_dir.substr(0, current_working_dir.find_last_of("\\/"));
       #else
		ENGINE_LOG_INFO("No implmentation for get executable full path on this platform.");
		return "";
       #endif // TOYRENDERER_PLATFORM_WINDOWS
    }
	void File::StyleAsPath(std::string & toStyle)
	{
        #ifdef TOYRENDERER_PLATFORM_WINDOWS

        std::replace(toStyle.begin(), toStyle.end(), '/', '\\');
        #endif
	}
}