#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
namespace sg
{
	class Node;
	class BaseRenderable;
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
		bool prepareDraw(std::shared_ptr<sg::Node>& root);
		bool draw();
		bool endDraw();

	private:
		Graphics::OpenGLGraphics& mOGLGraphics;
		glm::ivec2 mViewportSize;
		std::vector<s
	};
}