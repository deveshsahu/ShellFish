#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>

namespace Graphics
{
	class BaseRenderable;
	class Scene;
	class OpenGLGraphics
	{
	public:
		~OpenGLGraphics();
		OpenGLGraphics(OpenGLGraphics const&) = delete;
		void operator=(OpenGLGraphics const&) = delete;

		static OpenGLGraphics& getInstance();

		void render();

	private:
		OpenGLGraphics();


	};
}