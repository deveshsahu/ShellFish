#include "SceneGraphViewer.h"
#include "Graphics.h"
#include "RenderVisitor.h"
#include "Node.h"
#include "PerspectiveCamNode.h"
#include "OrthoCamNode.h"
#include "BackgroundRenderable.h"
#include "viewBufferObject.h"
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
		mViewBO = std::make_shared<Graphics::ViewBufferObject>();
		return true;
	}
	void SceneGraphViewer::render(std::weak_ptr<sg::Node> root)
	{
		if (auto rootNode = root.lock())
		{
			bool success = prepareDraw(rootNode);
			if (!success)
				return; // add error msg

			success = draw();
			if (!success)
				return; // add error msg

			success = endDraw();
			if (!success)
				return; // add error msg
		}
	}

	void SceneGraphViewer::setSceneDirty(bool dirty)
	{
		mSceneDirty = dirty;
	}

	void SceneGraphViewer::resizeWindow(int width, int height)
	{
		mViewportSize[0] = width;
		mViewportSize[1] = height;

		if (auto camnode = mCameraNode.lock())
		{
			auto camtype = camnode->getCameraType();
			double aspect_ratio = (double)width / (double)height;
			if (camtype == sg::CamType::ctPersp)
			{
				auto persp_cam_node = std::static_pointer_cast<sg::PerspectiveCamNode>(camnode);
				persp_cam_node->updateAspectRatio(aspect_ratio);
			}
			else if (camtype == sg::CamType::ctOrtho)
			{
				auto ortho_cam_node = std::static_pointer_cast<sg::OrthoCamNode>(camnode);
				ortho_cam_node->updateAspectRatio(aspect_ratio);
			}
			mViewBO->setProjectionMatrix(camnode->getProjectionMatrix());
		}
	}

	bool SceneGraphViewer::prepareDraw(std::shared_ptr<sg::Node>& root)
	{
		// Only perform prep if list is empty or scene is dirty	
		if (mSceneDirty)
		{
			auto renderVisitor = std::make_shared<RenderVisitor> (mRenderableList);
			root->visit(renderVisitor);
			for (auto& renderableWk : mRenderableList)
			{
				if (auto renderable = renderableWk.lock())
					renderable->init();
			}
			mCameraNode = renderVisitor->getCameraNode();
			mViewBO->init();
			mViewBO->setProjectionMatrix(renderVisitor->getProjectionMatrix());
			mViewBO->setViewMatrix(renderVisitor->getViewMatrix());
			Graphics::BackgroundRenderable::bkgInfo bkginfo;
			bkginfo.type = Graphics::BackgroundRenderable::bkgType::SOLID;
			mBackground = std::make_shared<Graphics::BackgroundRenderable>("bkg");
			mBackground->setInfo(bkginfo);
			if (!mBackground->init())
			{
				mBackground = nullptr;
			}
			mSceneDirty = false;
		}
		return true;
	}

	bool SceneGraphViewer::draw()
	{
		mOGLGraphics.viewport(0, 0, mViewportSize[0], mViewportSize[1]);
		mOGLGraphics.clear(glm::vec4(0.0, 0.0, 0.0, 1.f));
		mViewBO->update();
		mViewBO->bind();
		if (mBackground)
			mBackground->draw();
		for (auto& renderableWk : mRenderableList)
		{
			if (auto renderable = renderableWk.lock())
			{
				renderable->drawBegin();
				renderable->draw();
				renderable->drawEnd();
			}
		}
		return true;
	}

	bool SceneGraphViewer::endDraw()
	{
		return true;
	}
}