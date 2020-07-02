#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
namespace sg
{
	class Node;
}
namespace Graphics
{
	class OpenGLGraphics;
	class BaseRenderable;
	class BackgroundRenderable;
	class ViewBufferObject;
}
namespace view
{
	class SceneGraphViewer
	{
	public:
		SceneGraphViewer(const glm::ivec2& viewportSize);
		bool init();
		void render(std::weak_ptr<sg::Node> root);

		void setSceneDirty(bool dirty);

	private:
		bool prepareDraw(std::shared_ptr<sg::Node>& root);
		bool draw();
		bool endDraw();

	private:
		Graphics::OpenGLGraphics& mOGLGraphics;
		glm::ivec2 mViewportSize;
		std::vector < std::weak_ptr<Graphics::BaseRenderable >> mRenderableList;
		std::shared_ptr<Graphics::BackgroundRenderable> mBackground;
		std::shared_ptr<Graphics::ViewBufferObject> mViewBO;

		bool mSceneDirty = true;
	};
}