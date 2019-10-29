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

		/*std::shared_ptr<Scene>*/void createNewScene(int width, int height);
		void createSceneFromFile(const std::string& filename, int width, int height);

		void render();

	private:
		OpenGLGraphics();

		std::shared_ptr<Scene> mScene;
	};
}