#pragma once
#ifdef  TOYRENDERER_PLATFORM_WINDOWS
        #ifdef TOYRENDERER_BUILD_DLL
               #define TOYRENDERER_API __declspec(dllexport)
        #else
               #define TOYRENDERER_API __declspec(dllimport)
        #endif
#else 
#error Only Windows Support at the moment
#endif //  TOYRENDERER_PLATFORM_WINDOWS
 