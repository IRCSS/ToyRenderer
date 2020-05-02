#pragma once
#include "Core.h"
#include <string>



namespace ToyRenderer {

	static class TOYRENDERER_API File {

	public: 
		static std::string GetExecutableFullPath();
		static void        StyleAsPath(std::string& toStyle);
	};

}