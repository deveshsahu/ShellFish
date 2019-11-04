#pragma once
#include "glm/glm.hpp"
#include <memory>
namespace sg
{
	class Node;
}
namespace Graphics
{
	class OpenGLGraphics;
}
namespace view
{
	class SceneGraphViewer
	{
	public:
		SceneGraphViewer(const glm::ivec2& viewportSize);
		bool init();
		void render(std::weak_ptr<sg::Node> root);

	private:
		bool prepareDraw();
		bool draw();
		bool endDraw();

	private:
		Graphics::OpenGLGraphics& mOGLGraphics;
		glm::ivec2 mViewportSize;
	};
}