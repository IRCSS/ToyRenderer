#pragma once
#include <string>

// To Do Implement Later
namespace ToyRenderer {
	namespace Rendering {

		static class RHI {
		
		public: // TYPES

			enum Material_DepthFunction{ ALWAYS, NEVER, LESS, EQUAL, LEQUAL, GREATER,NOTEQUAL, GEQUAL};
		
		
		public:

			static void BindBackBuffer();

			static void BeginMarkerGroup( const std::string& markerName);
			static void EndMarkerGroup();


			static void EnableBackFaceCulling (const bool enable);
			static void EnableZTest           (const bool enable);
			static void EnableDepthBufferWrite(const bool enable);
            static void EnableBlend           (const bool enable);
			static void SetDepthFucntion      (const Material_DepthFunction depthFunction);

		};

	}
}