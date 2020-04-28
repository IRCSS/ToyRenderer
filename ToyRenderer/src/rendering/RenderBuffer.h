#pragma once
#include "Core.h"

namespace ToyRenderer {
	namespace Rendering {

		class RenderBuffer {
		// PUBLIC ======================================================================================
		public:
			enum Format {
				RGBA, Depth_16, Depth_24, Depth_32 
			};
		public:
			//Delete the copy constructor/assignment for All OpenGl Resources to avoid deleting reosurce on GPU on move/ coppy
			RenderBuffer(const RenderBuffer &) = delete;
			RenderBuffer &operator=(const RenderBuffer &) = delete;

			 RenderBuffer(unsigned int width, unsigned int heigth, const Format format);
			~RenderBuffer();

			void Bind()   const;
			void UnBind() const;
			unsigned int GetRendererID() const;

		// ______________________________________________________________________________________________
		// PRIVATE ======================================================================================
		private:
			unsigned int GetInternalFormat();

		private:
			unsigned int m_RendererID;
			unsigned int m_format;
			unsigned int m_width, m_heigth;



		};

	}
}