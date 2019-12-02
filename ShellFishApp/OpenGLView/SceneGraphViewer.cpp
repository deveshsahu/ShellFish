#include "SceneGraphViewer.h"
#include "Graphics.h"
#include "RenderVisitor.h"
namespace view
{
	SceneGraphViewer::SceneGraphViewer(const glm::ivec2& viewportSize):
		mOGLGraphics(Graphics::OpenGLGraphics::getInstance()),
		mViewportSize(viewportSize)
	{
	}

	bool SceneGraphViewer::init()
	{
		mOGLGraphics.initGL();
		mOGLGraphics.viewport(0, 0, mViewportSize[0], mViewportSize[1]);
		return true;
	}
	void SceneGraphViewer::render(std::weak_ptr<sg::Node> root)
	{
		if (auto rootNode = root.lock())
		{

			if (!draw())
			{
				return;
			}

			if (!endDraw())
			{
				return;
			}
		}
	}

	bool SceneGraphViewer::prepareDraw(std::shared_ptr<sg::Node>& root)
	{
		
		return true;
	}

	bool SceneGraphViewer::draw()
	{
		mOGLGraphics.clear(glm::vec4(0.0, 0.0, 0.0, 1.f));

		return true;
	}

	bool SceneGraphViewer::endDraw()
	{
		return true;
	}
}