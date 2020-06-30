#include "SceneGraphViewer.h"
#include "Graphics.h"
#include "RenderVisitor.h"
#include "Node.h"
#include "BaseRenderable.h"
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
			if (!prepareDraw(rootNode))
				return;

			for (auto& renderableWk : mRenderableList)
			{
				if (auto renderable = renderableWk.lock())
				{
					renderable->drawBegin();
					renderable->draw();
					renderable->drawEnd();
				}
			}
			/*if (!draw())
			{
				return;
			}

			if (!endDraw())
			{
				return;
			}*/
		}
	}

	void SceneGraphViewer::setSceneDirty(bool dirty)
	{
		mSceneDirty = dirty;
	}

	bool SceneGraphViewer::prepareDraw(std::shared_ptr<sg::Node>& root)
	{
		// Only perform prep if list is empty or scene is dirty	
		if (mRenderableList.empty() || mSceneDirty)
		{
			auto renderVisitor = std::make_shared<RenderVisitor> (mRenderableList);
			root->visit(renderVisitor);
			
			for (auto& renderableWk : mRenderableList)
			{
				if (auto renderable = renderableWk.lock())
				{
					//renderable->
				}
			}
		}

		return true;
	}

	bool SceneGraphViewer::draw()
	{
		mOGLGraphics.clear(glm::vec4(1.0, 0.0, 0.0, 1.f));

		return true;
	}

	bool SceneGraphViewer::endDraw()
	{
		return true;
	}
}