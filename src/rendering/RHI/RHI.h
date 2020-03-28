#pragma once
#include <string>

// To Do Implement Later
namespace ToyRenderer {
	namespace Rendering {

		static class RHI {
		public:

			static void BindBackBuffer();
			static void BeginMarkerGroup( const std::string& markerName);
			static void EndMarkerGroup();

		};

	}
}