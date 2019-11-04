#pragma once
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>

namespace Graphics
{
	class OpenGLGraphics
	{
	public:
		~OpenGLGraphics();
		OpenGLGraphics(OpenGLGraphics const&) = delete;
		void operator=(OpenGLGraphics const&) = delete;

		static OpenGLGraphics& getInstance();

		void initGL();

		void clear(const glm::vec4& color);
		void viewport(int x, int y, int sx, int sy);

	private:
		OpenGLGraphics();

		bool mInitGL = false;
	};
}